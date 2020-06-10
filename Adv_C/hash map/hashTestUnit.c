#include<stdio.h>
#include<stdlib.h>
#include"hashMap.h"
#include"myStruct.h"
#include"adt_error.h"
#define HUGE_LEN 10000
#define MY_PRIME 31
typedef enum
{
	SUCCESS,
	FAILED
} Result;

int PrintElement(const void* _key,void* _val,void* _context)
{
	mystruct* mys = (mystruct*) _val;
	int* key = (int*) _key;
	printf("Key i:%d struct:",*key);
	PrintMyStruct(mys,NULL);
	printf("\n");
	return 1;
}

size_t HashFunc(void* _val)
{
	size_t res = (*(int*)_val)*MY_PRIME;
	return res*(res+1)*MY_PRIME;
}

int KeyEqual(void* _val1,void* _val2)
{
	
	return (*(int*)_val1==*(int*)_val2);
}

void PrintResult(Result _res ,char _testName[] )
{
	printf("%s ",_testName);	
	switch(_res)
	{
		case SUCCESS:   printf("SUCCESS\n"); break;
		case FAILED: 	printf("FAILED\n"); break;
	}

}

void HashMap_Create_Valid()
{
	Result res; 
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(map)
	{
		res = SUCCESS;
		HashMap_Destroy(&map,NULL,FreeMyStruct);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_Create_Valid");
}

void HashMap_Create_Null_HashF()
{
	Result res; 
	HashMap* map = HashMap_Create(17,NULL,KeyEqual);
	if(map)
	{
		res = FAILED;
		HashMap_Destroy(&map,NULL,FreeMyStruct);
	}
	else
	{
		res = SUCCESS;
	}
	PrintResult(res , "HashMap_Create_Null_HashF");
}

void HashMap_Create_Null_EqualF()
{
	Result res; 
	HashMap* map = HashMap_Create(17,HashFunc,NULL);
	if(map)
	{
		res = FAILED;
		HashMap_Destroy(&map,NULL,FreeMyStruct);
	}
	else
	{
		res = SUCCESS;
	}
	PrintResult(res , "HashMap_Create_Null_EqualF");
}

void HashMap_Destroy_Vaild()
{
	
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	Result res = SUCCESS;
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Destroy_Vaild");
}

void HashMap_Destroy_Null()
{
	HashMap* map = NULL;
	Result res = SUCCESS;
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Destroy_Null");
}

void HashMap_Destroy_DuobleDestroy()
{
	
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	Result res = SUCCESS;
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Destroy_DuobleDestroy");
}

void HashMap_Insert_Valid()
{
	int i,keys[17];
	Result res = SUCCESS;
	mystruct* mys;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		mys = CreateMyStruct();
		if(MAP_SUCCESS!= HashMap_Insert(map,&keys[i],mys))
		{
			res = FAILED;
		}
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Insert_Valid");
}

void HashMap_Insert_Null()
{
	int i = 5;
	Result res = SUCCESS;
	HashMap* map = NULL;
	if(MAP_UNINITIALIZED_ERROR != HashMap_Insert(map,&i,NULL))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_Insert_Null");
}


void HashMap_Insert_Null_key()
{
	Result res = SUCCESS;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(MAP_KEY_NULL_ERROR != HashMap_Insert(map,NULL,NULL))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,NULL);
	PrintResult(res , "HashMap_Insert_Null_key");
}

void HashMap_Insert_DoubleInsert()
{
	int i = 3,keys[2]={1,2};
	Result res = SUCCESS;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(MAP_SUCCESS != HashMap_Insert(map,&i,&keys[i]))
	{
		res = FAILED;
	}
	if(MAP_KEY_DUPLICATE_ERROR != HashMap_Insert(map,&i,&keys[i]))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,NULL);
	PrintResult(res , "HashMap_Insert_DoubleInsert");
}

void HashMap_Insert_HugeInsert()
{
	int i,keys[HUGE_LEN];
	Result res = SUCCESS;
	mystruct* mys;
	HashMap* map = HashMap_Create(HUGE_LEN/2,HashFunc,KeyEqual);
	for(i=0;i<HUGE_LEN;i++)
	{
		keys[i]=i;
		mys = CreateMyStruct();
		if(MAP_SUCCESS!= HashMap_Insert(map,&keys[i],mys))
		{
			res = FAILED;
		}
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Insert_HugeInsert");
}

void HashMap_Remove_Vaild()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	mystruct* rem[17];
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	/*PrintMap(map);*/
	for(i=0;i<17;i++)
	{
		if(MAP_SUCCESS!= HashMap_Remove(map,&keys[i],(void**)&remkeys[i],(void**)&rem[i]))
		{
			res = FAILED;
		}
		FreeMyStruct(rem[i]);
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Remove_Vaild");
}


void HashMap_Remove_Null()
{
	int i = 5;
	int* b;
	mystruct* mys;
	Result res = SUCCESS;
	HashMap* map = NULL;
	if(MAP_UNINITIALIZED_ERROR != HashMap_Remove(map,&i,(void**)&b,(void**)&mys))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_Remove_Null");
}

void HashMap_Remove_Null_Key()
{
	int* b;
	mystruct* mys;
	Result res = SUCCESS;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(MAP_KEY_NULL_ERROR != HashMap_Remove(map,NULL,(void**)&b,(void**)&mys))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Remove_Null_Key");
}

void HashMap_Remove_Empty()
{
	int i = 5;
	int* b;
	mystruct* mys;
	Result res = SUCCESS;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(MAP_EMPTY_ERROR != HashMap_Remove(map,&i,(void**)&b,(void**)&mys))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Remove_Empty");
}

void HashMap_Remove_DoubleRemove()
{
	int *b,i=0;
	int * key = &i;
	Result res = SUCCESS;
	mystruct* mys = CreateMyStruct();
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	HashMap_Insert(map,key,mys);
	if(MAP_SUCCESS != HashMap_Remove(map,&i,(void**)&b,(void**)&mys))
	{
		res = FAILED;
	}
	if(MAP_EMPTY_ERROR != HashMap_Remove(map,&i,(void**)&b,(void**)&mys))
	{
		res = FAILED;
	}
	FreeMyStruct(mys);
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Remove_DoubleRemove");
}

void HashMap_Remove_HugeRemove()
{
	int i,keys[HUGE_LEN];
	int* remkeys[HUGE_LEN];
	Result res = SUCCESS;
	mystruct* mys;
	HashMap* map = HashMap_Create(HUGE_LEN/2,HashFunc,KeyEqual);
	for(i=0;i<HUGE_LEN;i++)
	{
		keys[i]=i;
		mys = CreateMyStruct();
		HashMap_Insert(map,&keys[i],mys);
	}
	for(i=0;i<HUGE_LEN;i++)
	{
		if(MAP_SUCCESS!= HashMap_Remove(map,&keys[i],(void**)&remkeys[i],(void**)&mys))
		{
			res = FAILED;
		}
		FreeMyStruct(mys);
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Remove_HugeRemove");
}


void HashMap_Find_Valid()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	mystruct* found;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	for(i=0;i<17;i++)
	{
		if(MAP_SUCCESS!=HashMap_Find(map,&keys[i],(void**)&found))
		{
			res = FAILED;
		}
	}
	
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Find_Valid");
}

void HashMap_Find_NotValid()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	mystruct* found;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	i = 30;
	if(MAP_SUCCESS==HashMap_Find(map,&i,(void**)&found))
	{
		res = FAILED;
	}

	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Find_NotValid");
}

void HashMap_Find_Null()
{
	int i = 5;
	mystruct* found;
	Result res = SUCCESS;
	HashMap* map = NULL;
	if(MAP_UNINITIALIZED_ERROR != HashMap_Find(map,&i,(void**)&found))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_Find_Null");
}

void HashMap_Find_Null_Key()
{
	mystruct* found;
	Result res = SUCCESS;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(MAP_KEY_NULL_ERROR != HashMap_Find(map,NULL,(void**)&found))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Find_Null_Key");
}

void HashMap_Find_Empty()
{
	int i = 5;
	mystruct* found;
	Result res = SUCCESS;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	if(MAP_EMPTY_ERROR != HashMap_Find(map,&i,(void**)&found))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Find_Empty");
}

void HashMap_Find_DoubleFind()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	mystruct* found;
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	i = 16;
	if(MAP_SUCCESS != HashMap_Find(map,&i,(void**)&found))
	{
		res = FAILED;
	}
	if(MAP_SUCCESS != HashMap_Find(map,&i,(void**)&found))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Find_DoubleFind");
}


void HashMap_Find_HugeFind()
{
	int i,keys[HUGE_LEN];
	int * remkeys[HUGE_LEN];
	Result res = SUCCESS;
	mystruct* mys[HUGE_LEN];
	mystruct* found;
	HashMap* map = HashMap_Create(HUGE_LEN/2,HashFunc,KeyEqual);
	for(i=0;i<HUGE_LEN;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	for(i=0;i<HUGE_LEN;i++)
	{
		if(MAP_SUCCESS!=HashMap_Find(map,&keys[i],(void**)&found))
		{
			res = FAILED;
		}
	}
	
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Find_HugeFind");
}


void HashMap_Rehash_Vaild()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	HashMap_Rehash(map,32);
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Rehash_Vaild");
}

void HashMap_Rehash_Null()
{
	Result res = SUCCESS;
	HashMap* map = NULL;
	if(MAP_UNINITIALIZED_ERROR != HashMap_Rehash(map,32))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_Rehash_Null");
}

void HashMap_Size_Vaild()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	if(HashMap_Size(map)!=17)
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_Size_Vaild");
}

void HashMap_Size_Null()
{
	Result res = SUCCESS;
	HashMap* map = NULL;
	if(HashMap_Size(map))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_Size_Null");
}

void HashMap_ForEach_Vaild()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	if(!HashMap_ForEach(map,PrintElement,NULL))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_ForEach_Vaild");
}

void HashMap_ForEach_Null_Func()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	if(HashMap_ForEach(map,NULL,NULL))
	{
		res = FAILED;
	}
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_ForEach_Null_Func");
}

void HashMap_ForEach_Null()
{
	Result res = SUCCESS;
	HashMap* map =NULL;
	if(HashMap_ForEach(map,PrintElement,NULL))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMap_ForEach_Null");
}

void HashMap_GetStatistics_Vaild()
{
	int i,keys[17];
	int * remkeys[17];
	Result res = SUCCESS;
	mystruct* mys[17];
	HashMap* map = HashMap_Create(17,HashFunc,KeyEqual);
	Map_Stats stats;
	for(i=0;i<17;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	stats = HashMap_GetStatistics(map);
	printf("\nMap Stats size 17:\n");
	printf("num of buckets: %lu\n", stats.numberOfBuckets);
	printf("num of chains: %lu\n", stats.numberOfChains);
	printf("max chain length: %lu\n", stats.maxChainLength);
	printf("average chain length: %lu\n", stats.averageChainLength);
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_GetStatistics_Vaild");
}

void HashMap_GetStatistics_Huge()
{
	int i,keys[HUGE_LEN];
	int * remkeys[HUGE_LEN];
	Result res = SUCCESS;
	mystruct* mys[HUGE_LEN];
	HashMap* map = HashMap_Create(HUGE_LEN*0.75,HashFunc,KeyEqual);
	Map_Stats stats;
	for(i=0;i<HUGE_LEN;i++)
	{
		keys[i]=i;
		remkeys[i]= &keys[i];
		mys[i] = CreateMyStruct();
		HashMap_Insert(map,remkeys[i],mys[i]);
		
	}
	stats = HashMap_GetStatistics(map);
	printf("\nBefore Rehash Map Stats size %.1f:\n",HUGE_LEN*0.75);
	printf("num of buckets: %lu\n", stats.numberOfBuckets);
	printf("num of chains: %lu\n", stats.numberOfChains);
	printf("max chain length: %lu\n", stats.maxChainLength);
	printf("average chain length: %lu\n", stats.averageChainLength);

	HashMap_Rehash(map,HUGE_LEN*2);
	stats = HashMap_GetStatistics(map);
	printf("\nAfter Rehash Map Stats size %d:\n",HUGE_LEN*2);
	printf("num of buckets: %lu\n", stats.numberOfBuckets);
	printf("num of chains: %lu\n", stats.numberOfChains);
	printf("max chain length: %lu\n", stats.maxChainLength);
	printf("average chain length: %lu\n", stats.averageChainLength);
	HashMap_Destroy(&map,NULL,FreeMyStruct);
	PrintResult(res , "HashMap_GetStatistics_Huge");
}

int main()
{
	printf("Create & destroy tests:\n");
	/*destroy & create tests*/
	HashMap_Create_Valid();
	HashMap_Create_Null_HashF();
	HashMap_Create_Null_EqualF();
	HashMap_Destroy_Vaild();
	HashMap_Destroy_Null();
	HashMap_Destroy_DuobleDestroy();

	/*insert  tests*/
	printf("\nInsert tests:\n");
	HashMap_Insert_Valid();
	HashMap_Insert_Null();
	HashMap_Insert_Null_key();
	HashMap_Insert_DoubleInsert();
	HashMap_Insert_HugeInsert();
	
	/*remove  tests*/
	printf("\nRemove tests:\n");
	HashMap_Remove_Vaild();
	HashMap_Remove_Null();
	HashMap_Remove_Null_Key();
	HashMap_Remove_Empty();
	HashMap_Remove_DoubleRemove();
	HashMap_Remove_HugeRemove();

	/*Find tests*/
	printf("\nFind tests:\n");
	HashMap_Find_Valid();
	HashMap_Find_NotValid();
	HashMap_Find_Null();
	HashMap_Find_Null_Key();
	HashMap_Find_Empty();
	HashMap_Find_DoubleFind();
	HashMap_Find_HugeFind();
	
	/*Rehash tests*/
	printf("\nRehash tests:\n");
	HashMap_Rehash_Vaild();
	HashMap_Rehash_Null();


	/*HashMap_Size*/
	printf("\nSize tests:\n");
	HashMap_Size_Vaild();
	HashMap_Size_Null();

	/*For each tests*/
	printf("\nFor each tests:\n");
	HashMap_ForEach_Vaild();
	HashMap_ForEach_Null_Func();
	HashMap_ForEach_Null();

	/*Map_Stats tests*/
	printf("\nMap Stats tests:\n");
	HashMap_GetStatistics_Vaild();
	HashMap_GetStatistics_Huge();

	return 0;
	
}










