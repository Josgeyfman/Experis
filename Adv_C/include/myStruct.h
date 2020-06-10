#ifndef __MY_STRUCT_H__
#define __MY_STRUCT_H__

/*testing struct*/

typedef struct MyStruct mystruct;

mystruct* CreateMyStruct();

void FreeMyStruct(void* _mys);

void PrintMyStruct(const void* _mys,void* context);

#endif
