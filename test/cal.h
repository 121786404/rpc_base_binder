#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "interface_def.h"


#define INHERIT_ICal(IName) \
    INHERIT_IBase(IName); \
    int     (*add)      ( IName * ,s32 ,s32 *);  \
    int     (*sub)      ( IName * ,s32 ,s32 *)

DEFINE_INTERFACE(ICal);


MAE_Ret Cal_New(void **ppObj);

#define ICal_QueryInterface(pICntlr, id, pp, po)           GET_FUNCTBL((pICntlr), ICal)->QueryInterface(pICntlr, id, pp, po)
#define ICal_Add(pICntlr,p1,p2)           GET_FUNCTBL((pICntlr), ICal)->add(pICntlr,p1,p2)
#define ICal_Sub(pICntlr,p1,p2)           GET_FUNCTBL((pICntlr), ICal)->sub(pICntlr,p1,p2)


