#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "binder.h"
#include "test_server.h"


//#include "MI_Count.h"
#define ALOGI(x...) fprintf(stderr, "test: " x)
#define ALOGE(x...) fprintf(stderr, "test: " x)


static struct binder_state *g_bs;
static uint32_t g_handle;

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


int MI_Count_Init(int chn)
{
    struct binder_state* bs;  
    uint32_t handle;
    uint32_t svcmgr = BINDER_SERVICE_MANAGER;
    char cal_str[5] = {0};

    if(g_handle)
    {
        ALOGI("chn:[%d] has inited\n",chn);
        return 0;
    }

    ALOGI("%s %d chn:%d\n",__FUNCTION__,__LINE__,chn);

    bs = binder_open(128*1024);
    if (!bs) {
        fprintf(stderr, "failed to open binder driver\n");
        return -1;
    }
	g_bs = bs;


	/* get service */
    sprintf(cal_str,"cal_%d",chn);
	handle = svcmgr_lookup(g_bs, svcmgr,cal_str);
	if (!handle) {
        fprintf(stderr, "failed to get cal_1 service\n");
        return -1;
	}
	g_handle = handle;

	//fprintf(stderr, "Handle for cal_1 service = %d\n", g_handle);
}


int MI_Count_Enable(int chn)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	int ret;

    if(g_handle == 0)
    {
        MI_Count_Init(chn);
        if(g_handle == 0)
            return -1;
    }

    ALOGI("%s %d chn:%d\n",__FUNCTION__,__LINE__,chn);


	/* 构造binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header

	/* 放入参数 */
    bio_put_uint32(&msg, chn);

	/* 调用binder_call */
	if (binder_call(g_bs, &msg, &reply, g_handle, COUNT_SVR_CMD_ENABLE))
		return 0;

	/* 从reply中解析出返回值 */
	ret = bio_get_uint32(&reply);

	binder_done(g_bs, &msg, &reply);

	return ret;
}


int MI_Count_Set(int chn,int num)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	int ret;   

    if(g_handle == 0)
        return -1;

    ALOGI("%s %d chn:%d num:%d\n",__FUNCTION__,__LINE__,chn,num);

    /* 构造binder_io */
    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header

    /* 放入参数 */
    bio_put_uint32(&msg, chn);
    bio_put_uint32(&msg, num);

    /* 调用binder_call */
    if (binder_call(g_bs, &msg, &reply, g_handle, COUNT_SVR_CMD_GET))
        return 0;

    /* 从reply中解析出返回值 */
    ret = bio_get_uint32(&reply);

    binder_done(g_bs, &msg, &reply);

    return ret;
}

int MI_Count_Add(int chn,int num)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	int ret;   

    if(g_handle == 0)
        return -1;

    ALOGI("%s %d chn:%d num:%d\n",__FUNCTION__,__LINE__,chn,num);
    /* 构造binder_io */
    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header

    /* 放入参数 */
    bio_put_uint32(&msg, chn);
    bio_put_uint32(&msg, num);

    /* 调用binder_call */
    if (binder_call(g_bs, &msg, &reply, g_handle, COUNT_SVR_CMD_ADD))
        return 0;

    /* 从reply中解析出返回值 */
    ret = bio_get_uint32(&reply);

    binder_done(g_bs, &msg, &reply);

    return ret;
}

int MI_Count_Sub(int chn,int num)
{
    unsigned iodata[512/4];
    struct binder_io msg, reply;
    int ret;   

    if(g_handle == 0)
        return -1;

    ALOGI("%s %d chn:%d num:%d\n",__FUNCTION__,__LINE__,chn,num);

    /* 构造binder_io */
    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header

    /* 放入参数 */
    bio_put_uint32(&msg, chn);
    bio_put_uint32(&msg, num);

    /* 调用binder_call */
    if (binder_call(g_bs, &msg, &reply, g_handle, COUNT_SVR_CMD_SUB))
        return 0;

    /* 从reply中解析出返回值 */
    ret = bio_get_uint32(&reply);

    binder_done(g_bs, &msg, &reply);
    
    return ret;
}

int MI_Count_Get(int chn,int* pNum)
{
    unsigned iodata[512/4];
    struct binder_io msg, reply;
    int ret;   

    if(g_handle == 0)
        return -1;

    ALOGI("%s %d chn:%d \n",__FUNCTION__,__LINE__,chn);

    /* 构造binder_io */
    bio_init(&msg, iodata, sizeof(iodata), 4);
    bio_put_uint32(&msg, 0);  // strict mode header

    /* 放入参数 */
    bio_put_uint32(&msg, chn);
    bio_put_uint32(&msg, (uint32_t)pNum);

    /* 调用binder_call */
    if (binder_call(g_bs, &msg, &reply, g_handle, COUNT_SVR_CMD_GET))
        return 0;

    /* 从reply中解析出返回值 */
    ret = bio_get_uint32(&reply);

    binder_done(g_bs, &msg, &reply);
    
    return ret;
}


int main()
{
	int ret;
	int num;
    
    int chn = 2;//rand()%3;

    MI_Count_Enable(chn);
    
    num = rand()%100;
    MI_Count_Add(chn,num);
    MI_Count_Get(chn,&ret);
	ALOGI("chn:[%d] num = %d\n", chn,num);

    num = rand()%100;
    MI_Count_Sub(chn,num);
    MI_Count_Get(chn,&ret);
	ALOGI("chn:[%d] num = %d\n", chn,num);

	return 0;
}
