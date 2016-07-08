#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdint.h>
#include <assert.h>
#include "cal.h"
#include "call_server.h"
#include "binder.h"

typedef struct Cal_TAG
{
	DECLARE_FUNCTBL(ICal);   /// function table pointer
	u32 refCnt;
    struct binder_state *bs;
    uint32_t cal_handle;
} Cal;

static Cal* gCalPtr;

static u32 Cal_AddRef(ICal *pICAL)
{
	u32 uRefCnt = 0;
	Cal *pThis = (Cal *)pICAL;

	do
	{
		if (NULL == pThis)
		{
			break;
		}

		/* Add referent count */
		(pThis->refCnt)++;
		uRefCnt = pThis->refCnt;
	} while (FALSE);

	return uRefCnt;
}

static u32 Cal_Release(ICal *pICAL)
{
	Cal *pThis = (Cal *)pICAL;
	u32 nRefCnt = 0;
	MAE_Ret nRet = MAE_RET_SUCCESS;

	do
	{
		if (NULL == pICAL)
		{
			assert(FALSE);
			break;
		}

		nRefCnt = --(pThis->refCnt);
		if (0 == nRefCnt)
		{
            binder_release(pThis->bs, pThis->cal_handle);
            free(pThis);
			gCalPtr = NULL;
		}
	} while (FALSE);

	return nRet;
}

static MAE_Ret Cal_QueryInterface(ICal *pICAL, MAE_IId iId, void **ppObj, IBase *pOwner)
{
	return 0;
}

MAE_Ret Cal_Add(ICal *pICAL ,s32 p1 , s32* p2)
{
	Cal *pThis = (Cal *)pICAL;
	MAE_Ret nRet = MAE_RET_SUCCESS;

	unsigned iodata[512/4];
	struct binder_io msg, reply;
	MAE_Ret ret = MAE_RET_SUCCESS;

	/* 构造binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header

	/* 放入参数 */
    bio_put_uint32(&msg, p1);

	/* 调用binder_call */
	if (binder_call(pThis->bs, &msg, &reply, pThis->cal_handle, CAL_SVR_CMD_ADD))
		return 0;

	/* 从reply中解析出返回值 */
	*p2 = bio_get_uint32(&reply);
	binder_done(pThis->bs, &msg, &reply);

	return ret;
}

MAE_Ret Cal_Sub(ICal *pICAL ,s32 p1 , s32* p2)
{
	Cal *pThis = (Cal *)pICAL;
	MAE_Ret nRet = MAE_RET_SUCCESS;

	unsigned iodata[512/4];
	struct binder_io msg, reply;
	MAE_Ret ret = MAE_RET_SUCCESS;

	/* 构造binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header

	/* 放入参数 */
    bio_put_uint32(&msg, p1);

	/* 调用binder_call */
	if (binder_call(pThis->bs, &msg, &reply, pThis->cal_handle, CAL_SVR_CMD_SUB))
		return 0;

	/* 从reply中解析出返回值 */
	*p2 = bio_get_uint32(&reply);
	binder_done(pThis->bs, &msg, &reply);
}


static const FUNCTBL(ICal) ICal_Ftbl =
{
	Cal_AddRef
	,Cal_Release
	,Cal_QueryInterface
	,Cal_Add
	,Cal_Sub
};

static uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *name)
{
    uint32_t handle;
    unsigned iodata[512/4];
    struct binder_io msg, reply;

    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header
    bio_put_string16_x(&msg, SVC_MGR_NAME);
    bio_put_string16_x(&msg, name);

    if (binder_call(bs, &msg, &reply, target, SVC_MGR_CHECK_SERVICE))
        return 0;

    handle = bio_get_ref(&reply);

    if (handle)
        binder_acquire(bs, handle);

    binder_done(bs, &msg, &reply);

    return handle;
}


MAE_Ret Cal_New(void **ppObj)
{
	MAE_Ret ret = MAE_RET_SUCCESS;
	Cal *pThis = NULL;
    uint32_t svcmgr = BINDER_SERVICE_MANAGER;
    uint32_t handle;
    struct binder_state *bs;

	if (gCalPtr)
	{
		*ppObj = gCalPtr;
		return MAE_RET_SUCCESS;
	}

	pThis = malloc(sizeof(Cal));
	pThis->Vtbl_Ptr = &ICal_Ftbl;
	*ppObj = (Cal *)pThis;

    bs = binder_open(128*1024);
    if (!bs) {
        fprintf(stderr, "failed to open binder driver\n");
        return MAE_RET_FAILED;
    }
    pThis->bs = bs;

	/* get service */
	handle = svcmgr_lookup(pThis->bs, svcmgr, "cal");
	if (!handle) {
        fprintf(stderr, "failed to get cal service\n");
        return MAE_RET_FAILED;
	}

	pThis->cal_handle = handle;
	fprintf(stderr, "Handle for cal service = %d\n", pThis->cal_handle);

    gCalPtr = pThis;
	return ret;
}

