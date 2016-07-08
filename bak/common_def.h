#pragma once


typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef long long s64;
typedef int s32;
typedef short s16;
typedef signed char s8;

typedef u16 MAE_ClsId; ///< type for class ids
typedef u32 MAE_IId; ///< type for interface ids
typedef u32 MAE_Ret; ///< type for MAE return values
typedef u16 MAE_WChar; ///< type for MAE defined wide characters
typedef u32 MAE_EventId; ///< type for events used in the communication of IHandler objects

						 /// type aliases
typedef MAE_IId MAEIId_t;
typedef MAE_ClsId MAEClsId_t;
typedef MAE_Ret MAERet_t;
typedef MAE_EventId MAEEvent_t;


enum
{
	MAE_RET_SUCCESS = 0, ///< operation completed successfully
	MAE_RET_BAD_PARAM = 1, ///< invalid input parameters
	MAE_RET_FAILED = 2, ///< WHAT? every code here is failed
};

#define TRUE  1
#define FALSE 0


