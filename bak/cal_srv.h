#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "interface_def.h"


#define INHERIT_ICalSrv(IName) \
    INHERIT_IBase(IName); \
    int     (*sum)      ( IName * );  \
    int     (*sub)      ( IName * );  \
    int     (*get)      ( IName * ,u32 *)

DEFINE_INTERFACE(ICalSrv);


MAE_Ret Calsrv_New(void **ppObj);

#define ICalSrv_QueryInterface(pICntlr, id, pp, po)           GET_FUNCTBL((pICntlr), ICalSrv)->QueryInterface(pICntlr, id, pp, po)
#define ICalSrv_Inc(pICntlr)           GET_FUNCTBL((pICntlr), ICalSrv)->sum(pICntlr)
#define ICalSrv_Sub(pICntlr)           GET_FUNCTBL((pICntlr), ICalSrv)->sub(pICntlr)
#define ICalSrv_Get(pICntlr ,p1)       GET_FUNCTBL((pICntlr), ICalSrv)->get(pICntlr ,p1)


