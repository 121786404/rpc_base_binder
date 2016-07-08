#pragma once

#include "common_def.h"


//
// macros to define an interface
//
// macro that denotes the name of the function table structure of an interface
#define FUNCTBL(IName)				IName##_Vtbl

// macro to declare the pointer of the function table when defining an interface
#define DECLARE_FUNCTBL(IName)		const IName##_Vtbl *Vtbl_Ptr
// ZINC: obsolete macro for virtual function table and other stuff
#define DECLARE_CMN_COMPNT DECLARE_FUNCTBL

// macro to define the structure of virtual function names and prototypes of an interface
#define DEFINE_FUNCTBL(IName) \
	typedef struct IName##_Vtbl_tag FUNCTBL(IName); \
	struct IName##_Vtbl_tag

//
// NOTE: customize INHERIT_IName before using DEFINE_INTERFACE macro
//
// Macro to define the virtual function table and the base structure of an interface.
// Any object implements an interface shall have that interface structure defined as
// the first member in the object
#define DEFINE_INTERFACE(IName) \
	typedef struct IName##_tag IName; \
	DEFINE_FUNCTBL(IName) \
	{ INHERIT_##IName(IName); }; \
	struct IName##_tag \
	{ DECLARE_FUNCTBL(IName); }


/*=============================================================*/
// IBase interface
/*=============================================================*/
// methods of IBase interface
#define INHERIT_IBase(IName) \
	u32 (*AddRef)(IName*); \
	u32 (*Release)(IName*); \
	MAERet_t (*QueryInterface)(IName*, MAEIId_t, void**, IBase*)


// defines the base structure of an IBase object
DEFINE_INTERFACE(IBase);

#define GET_FUNCTBL(pObj, IName)	(((IName*)pObj)->Vtbl_Ptr)

