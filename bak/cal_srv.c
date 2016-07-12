#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <assert.h>
#include "cal_srv.h"




typedef struct CalSrv_TAG
{
	DECLARE_FUNCTBL(ICalSrv);   /// function table pointer
	u32 refCnt;
	u32 num;
} CalSrv;

static CalSrv* gCalPtr;

static u32 CalSrv_AddRef(ICalSrv *pICALSRV)
{
	u32 uRefCnt = 0;
	CalSrv *pThis = (CalSrv *)pICALSRV;

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

static u32 CalSrv_Release(ICalSrv *pICALSRV)
{
	CalSrv *pThis = (CalSrv *)pICALSRV;
	u32 nRefCnt = 0;
	MAE_Ret nRet = MAE_RET_SUCCESS;

	do
	{
		if (NULL == pICALSRV)
		{
			assert(FALSE);
			break;
		}

		nRefCnt = --(pThis->refCnt);
		if (0 == nRefCnt)
		{
			free(pThis);
			gCalPtr = NULL;
		}
	} while (FALSE);

	return nRet;
}

static MAE_Ret CalSrv_QueryInterface(ICalSrv *pICALSRV, MAE_IId iId, void **ppObj, IBase *pOwner)
{
	return 0;
}

MAE_Ret CalSrv_Inc(ICalSrv *pICALSRV)
{
	CalSrv *pThis = (CalSrv *)pICALSRV;
	MAE_Ret nRet = MAE_RET_SUCCESS;
	pThis->num++;
	return nRet;
}

MAE_Ret CalSrv_Sub(ICalSrv *pICALSRV)
{
	CalSrv *pThis = (CalSrv *)pICALSRV;
	MAE_Ret nRet = MAE_RET_SUCCESS;
	pThis->num--;
	return nRet;
}

MAE_Ret CalSrv_Get(ICalSrv *pICALSRV , u32* pNum)
{
	CalSrv *pThis = (CalSrv *)pICALSRV;
	MAE_Ret nRet = MAE_RET_SUCCESS;
	*pNum = pThis->num;
	return nRet;
}

static const FUNCTBL(ICalSrv) ICalSrv_Ftbl =
{
	CalSrv_AddRef
	,CalSrv_Release
	,CalSrv_QueryInterface
	,CalSrv_Inc
	,CalSrv_Sub
	,CalSrv_Get
};



MAE_Ret Calsrv_New(void **ppObj)
{
	MAE_Ret ret = MAE_RET_SUCCESS;
	CalSrv *pThis = NULL;

	if (gCalPtr)
	{
		*ppObj = gCalPtr;
		return MAE_RET_SUCCESS;
	}

	pThis = malloc(sizeof(CalSrv));
	pThis->Vtbl_Ptr = &ICalSrv_Ftbl;
	*ppObj = (CalSrv *)pThis;

	gCalPtr = pThis;


	gCalPtr->num = 1000000;

	return ret;
}


