#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "cal_srv.h"

int main()
{
    int ret;
    u32 num;
    ICalSrv* srv;
    Calsrv_New(&srv);

    printf("---inc---\n");
    ret = ICalSrv_Inc(srv);

    ret = ICalSrv_Get(srv ,&num);
    printf("num = %d\n", num);
    
    printf("---sub---\n");
    ret = ICalSrv_Sub(srv);

    ret = ICalSrv_Get(srv, &num);
    printf("num = %d\n", num);

    return 0;
}
