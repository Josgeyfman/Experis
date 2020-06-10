#include<stdio.h>
#include<stdlib.h>
#include"hash.h"
#include"adt_error.h"
#define HUGE_LEN 10000

typedef enum{
		SUCCESS,
		FAILED
} Result;

void PrintVal(const void* _element ,void* _context)
{
	int* el = (int*)_element;
	printf("%d,",*el);
}

size_t HashFunc(int _val)
{
	return (_val*_val)*7;
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

void HashCreate_Valid()
{
	Result res; 
	Hash* hash = HashCreate(17,HashFunc);
	if(hash)
	{
		res = SUCCESS;
		HashDestroy(&hash);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HashCreate_Valid");
}

void HashDestroy_Vaild()
{
	
	Hash* hash = HashCreate(17,HashFunc);
	Result res = SUCCESS;
	HashDestroy(&hash);
	PrintResult(res , "HashDestroy_Vaild");
}

void HashDestroy_Null()
{
	Hash* hash = NULL;
	Result res = SUCCESS;
	HashDestroy(&hash);
	PrintResult(res , "HashDestroy_Null");
}

void HashDestroy_DuobleDestroy()
{
	
	Hash* hash = HashCreate(17,HashFunc);
	Result res = SUCCESS;
	HashDestroy(&hash);
	HashDestroy(&hash);
	PrintResult(res , "HashDestroy_DuobleDestroy");
}

void HashInsert_Valid()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<17;i++)
	{
		if(ERR_SUCCESS!= HashInsert(hash,i))
		{
			res = FAILED;
		}
	}
	/*HashPrint(hash);*/
	HashDestroy(&hash);
	PrintResult(res , "HashInsert_Valid");
}

void HashInsert_Null()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = NULL;
	for(i=0;i<17;i++)
	{
		if(ERR_SUCCESS == HashInsert(hash,i))
		{
			res = FAILED;
		}
	}
	PrintResult(res , "HashInsert_Null");
}

void HashInsert_DoubleInsert()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<2;i++)
	{
		if(ERR_SUCCESS!= HashInsert(hash,i))
		{
			res = FAILED;
		}
	}
	/*HashPrint(hash);*/
	HashDestroy(&hash);
	PrintResult(res , "HashInsert_DoubleInsert");
}

void HashInsert_HugeInsert()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(HUGE_LEN,HashFunc);
	for(i=0;i<HUGE_LEN;i++)
	{
		if(ERR_SUCCESS!= HashInsert(hash,i))
		{
			res = FAILED;
		}
	}
	/*HashPrint(hash);*/
	HashDestroy(&hash);
	PrintResult(res , "HashInsert_HugeInsert");
}

void HashRemove_Vaild()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<17;i++)
	{
		HashInsert(hash,i);
	}
	for(i=0;i<17;i++)
	{
		/*printf("rem %d: ",i);*/
		if(ERR_SUCCESS!= HashRemove(hash,i))
		{
			res = FAILED;
		}
		/*HashPrint(hash);*/
	}
	
	HashDestroy(&hash);
	PrintResult(res , "HashRemove_Vaild");
}

void HashRemove_Null()
{
	int i = 5;
	Result res = SUCCESS;
	Hash* hash = NULL;
	if(ERR_SUCCESS == HashRemove(hash,i))
	{
		res = FAILED;
	}
	PrintResult(res , "HashRemove_Null");
}

void HashRemove_Empty()
{
	int i = 5;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	if(ERR_SUCCESS== HashRemove(hash,i))
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashRemove_Empty");
}

void HashRemove_DoubleRemove()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<2;i++)
	{
		HashInsert(hash,i);
	}
	for(i=0;i<2;i++)
	{
		if(ERR_SUCCESS!= HashRemove(hash,i))
		{
			res = FAILED;
		}
	}
	HashDestroy(&hash);
	PrintResult(res , "HashRemove_DoubleRemove");
}

void HashRemove_HugeRemove()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(HUGE_LEN,HashFunc);
	for(i=0;i<HUGE_LEN;i++)
	{
		HashInsert(hash,i);
	}
	for(i=0;i<HUGE_LEN;i++)
	{
		/*printf("rem %d: ",i);*/
		if(ERR_SUCCESS!= HashRemove(hash,i))
		{
			res = FAILED;
		}
		/*HashPrint(hash);*/
	}
	HashDestroy(&hash);
	PrintResult(res , "HashRemove_HugeRemove");
}


void HashIsFound_Valid()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<17;i++)
	{
		HashInsert(hash,i);
	}
	for(i=0;i<17;i++)
	{
		/*printf("rem %d: ",i);*/
		if(!HashIsFound(hash,i))
		{
			res = FAILED;
		}
		/*HashPrint(hash);*/
	}
	
	HashDestroy(&hash);
	PrintResult(res , "HashIsFound_Valid");
}

void HashIsFound_Null()
{
	int i = 5;
	Result res = SUCCESS;
	Hash* hash = NULL;
	if(HashIsFound(hash,i))
	{
		res = FAILED;
	}
	PrintResult(res , "HashIsFound_Null");
}

void HashIsFound_Empty()
{
	int i = 5;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	if(HashRemove(hash,i))
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashIsFound_Empty");
}

void HashIsFound_DoubleFind()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<2;i++)
	{
		HashInsert(hash,i);
	}
	for(i=0;i<2;i++)
	{
		if(!HashIsFound(hash,i))
		{
			res = FAILED;
		}
	}
	HashDestroy(&hash);
	PrintResult(res , "HashIsFound_DoubleFind");
}

void HashIsFound_HugeFInd()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(HUGE_LEN,HashFunc);
	
	for(i=0;i<HUGE_LEN;i++)
	{
		/*printf("rem %d: ",i);*/
		if(!HashIsFound(hash,i))
		{
			res = FAILED;
		}
		/*HashPrint(hash);*/
	}
	HashDestroy(&hash);
	PrintResult(res , "HashIsFound_HugeFInd");
}

void HashCapacity_Vaild()
{
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	if(HashCapacity(hash)!=17)
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashCapacity_Vaild");
}

void HashCapacity_Null()
{
	Result res = SUCCESS;
	Hash* hash = NULL;
	if(HashCapacity(hash))
	{
		res = FAILED;
	}
	PrintResult(res , "HashCapacity_Null");
}

void HashNumOfItems_Vaild()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<HUGE_LEN;i++)
	{
		HashInsert(hash,i);
	}
	if(HashNumOfItems(hash)!=17)
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashNumOfItems_Vaild");
}

void HashNumOfItems_Null()
{
	Result res = SUCCESS;
	Hash* hash = NULL;
	if(HashNumOfItems(hash))
	{
		res = FAILED;
	}
	PrintResult(res , "HashNumOfItems_Null");
}


void HashAverageRehashes_Vaild()
{
	int i;
	double average =  14./17.;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<17;i++)
	{
		HashInsert(hash,i);
	}
	if(HashAverageRehashes(hash)!=average)
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashAverageRehashes_Vaild");
}

void HashAverageRehashes_Null()
{
	Result res = SUCCESS;
	Hash* hash = NULL;
	if(HashAverageRehashes(hash))
	{
		res = FAILED;
	}
	PrintResult(res , "HashAverageRehashes_Null");
}

void HashAverageRehashes_Empty()
{
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	if(HashAverageRehashes(hash))
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashAverageRehashes_Empty");
}

void HashAverageRehashes_Huge()
{
	int i;
	double average = 1.472500;
	Result res = SUCCESS;
	Hash* hash = HashCreate(HUGE_LEN,HashFunc);
	for(i=0;i<HUGE_LEN;i++)
	{
		HashInsert(hash,i);
	}
	if(HashAverageRehashes(hash)!=average)
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashAverageRehashes_Huge");
}

void HashMaxReHash_Vaild()
{
	int i;
	Result res = SUCCESS;
	Hash* hash = HashCreate(17,HashFunc);
	for(i=0;i<17;i++)
	{
		HashInsert(hash,i);
	}
	if(HashMaxReHash(hash)!=5)
	{
		res = FAILED;
	}
	HashDestroy(&hash);
	PrintResult(res , "HashMaxReHash_Vaild");
}

void HashMaxReHash_Null()
{
	Result res = SUCCESS;
	Hash* hash = NULL;
	if(HashMaxReHash(hash))
	{
		res = FAILED;
	}
	PrintResult(res , "HashMaxReHash_Null");
}

int main()
{
	printf("Create & destroy tests:\n");
	/*destroy & create tests*/
	HashCreate_Valid();
	HashDestroy_Vaild();
	HashDestroy_Null();
	HashDestroy_DuobleDestroy();

	/*insert  tests*/
	printf("\nInsert tests:\n");
	HashInsert_Valid();
	HashInsert_Null();
	HashInsert_DoubleInsert();
	HashInsert_HugeInsert();
	
	/*remove  tests*/
	printf("\nRemove tests:\n");
	HashRemove_Vaild();
	HashRemove_Null();
	HashRemove_Empty();
	HashRemove_DoubleRemove();
	HashRemove_HugeRemove();

	/*Is found tests*/
	printf("\nIs found tests:\n");
	HashIsFound_Valid();
	HashIsFound_Null();
	HashIsFound_DoubleFind();
	HashIsFound_HugeFInd();
	
	/*HashCapacity tests*/
	printf("\nHashCapacity tests:\n");
	HashCapacity_Vaild();
	HashCapacity_Null();

	/*HashNumOfItems tests*/
	printf("\nHashNumOfItems tests:\n");
	HashNumOfItems_Vaild();
	HashNumOfItems_Null();

	/*HashAverageRehashes tests*/
	printf("\nHashAverageRehashes tests:\n");
	HashAverageRehashes_Vaild();
	HashAverageRehashes_Huge();
	HashAverageRehashes_Null();
	HashAverageRehashes_Empty();
	

	/*HashMaxReHash tests*/
	printf("\nHashMaxReHash tests:\n");
	HashMaxReHash_Vaild();
        HashMaxReHash_Null();

	return 0;
	
}










