#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "cal.h"

int main()
{
	int ret;
	s32 num = 0;
	ICal* srv;
	Cal_New((void **)&srv);

	printf("---inc---\n");

	ret = ICal_Add(srv,1,&num);
	printf("num = %d\n", num);
	
	printf("---sub---\n");
	ret = ICal_Sub(srv,2,&num);

	printf("num = %d\n", num);

	return 0;
}
