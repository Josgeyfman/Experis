#include <stdlib.h> 	/*allocation*/
#include <math.h>   	/*sqrt*/
#include <stdio.h>  	/*printf*/
#include "adt_error.h"  /*ERRCODE*/
#include "hash.h"

#define MAGIC_NUM 0xadaddead
#define NOT_MAGIC_NUM 0xdadabeaf
#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)
#define EXPAND_CAP 1.3

enum {INIT,EMPTY,USED};

struct Hash
{
	size_t m_magicNum;
	int* m_data;
	char* m_state;
	size_t m_hashSize; 		/*original size given by the client*/
	size_t m_capacity; 		/*real hush size */
	size_t m_numOfItems; 		/*number of occupied plases in the table*/
	size_t m_maxOfRehashOperations; /*maximum emaunt of rehash opetations which have been done over one insertion*/
	size_t m_counterOfInsertions; 	/*maximum emaunt of insertions into the table*/
	size_t m_allRehashOperations; 	/*all rehash operations mutual counter*/
	hashFunction m_hashF;
};

/*----------------------------------static function signatures----------------------------------*/

static int IsPrime(size_t _num);
static int GetNextPrime(size_t _num);
static int IsFound(const Hash* _hash, int _data);
static int FindRehashIndex(const Hash* _hash,size_t _hashVal,int _data);
static void InsertData(Hash* _hash,size_t _hashVal,int _data);

/*----------------------------------API functions -----------------------------------------------*/

Hash* HashCreate(size_t _size,hashFunction _hashF)
{
	Hash* hashp = NULL;

	if(!_hashF || _size==0)
	{
		return hashp;
	}

	hashp = (Hash*)malloc(sizeof(Hash));
	if(!hashp)
	{
		return hashp;
	}

	hashp->m_capacity = GetNextPrime(_size*EXPAND_CAP);

	hashp->m_data= (int*)calloc(hashp->m_capacity,sizeof(int));
	if(!hashp->m_data)
	{
		free(hashp);
		return NULL;
	}

	hashp->m_state= (char*)calloc(hashp->m_capacity,sizeof(char));
	if(!hashp->m_state)
	{
		free(hashp->m_data);
		free(hashp);
		return NULL;
	}

	hashp->m_hashSize = _size;
	hashp->m_numOfItems = 0;
	hashp->m_maxOfRehashOperations = 0;
	hashp->m_counterOfInsertions = 0;
	hashp->m_allRehashOperations = 0;
	hashp->m_hashF = _hashF;
	hashp->m_magicNum = MAGIC_NUM;

	return hashp;
}

void HashDestroy(Hash** _hash)
{
	if(!IS_VALID((*_hash)))
	{
		return;
	}
	(*_hash)->m_magicNum = NOT_MAGIC_NUM;
	free((*_hash)->m_state);
	free((*_hash)->m_data);
	free(*_hash);
	*_hash = NULL;
}

ERRCODE HashInsert(Hash* _hash, int _data)
{
	size_t hashVal,reHashCount = 0;
	if(!IS_VALID(_hash))
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	if(IsFound(_hash,_data))
	{
		return ERR_EXISTS;
	}

	if(_hash->m_hashSize == _hash->m_numOfItems)
	{
		return ERR_FULL;
	}
	
	hashVal = _hash->m_hashF(_data) % _hash->m_capacity;

	if(_hash->m_state[hashVal] == INIT || _hash->m_state[hashVal] == EMPTY )
	{
		InsertData(_hash,hashVal,_data);
		return ERR_SUCCESS;
	}
	
	while(_hash->m_state[hashVal]==USED)
	{
		hashVal++;
		hashVal %= _hash->m_capacity;
		_hash->m_allRehashOperations++;
		reHashCount++;
	}

	if(_hash->m_maxOfRehashOperations < reHashCount)
	{
		_hash->m_maxOfRehashOperations = reHashCount;
	}
	
	InsertData(_hash,hashVal,_data);

	return ERR_SUCCESS;
}

int HashIsFound(const Hash* _hash, int _data)
{
	if(!IS_VALID(_hash))
	{
		return 0;
	}
	return (IsFound(_hash,_data)>-1) ;
}

ERRCODE HashRemove(Hash* _hash, int _data)
{
	size_t hashVal;
	if(!IS_VALID(_hash))
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	if(!IsFound(_hash,_data))
	{
		return ERR_NOT_EXISTS;
	}

	if(_hash->m_numOfItems == 0)
	{
		return ERR_EMPTY;
	}

	hashVal = _hash->m_hashF(_data) % _hash->m_capacity;

	if(_hash->m_state[hashVal]==USED && _hash->m_data[hashVal] == _data)
	{
		_hash->m_state[hashVal]=EMPTY;
		_hash->m_numOfItems--;
		return ERR_SUCCESS;
	}
	
	hashVal = FindRehashIndex(_hash,hashVal,_data);

	_hash->m_numOfItems--;
	_hash->m_state[hashVal]=EMPTY;
	return ERR_SUCCESS;
}

size_t HashNumOfItems(const Hash* _hash)
{
	if(!IS_VALID(_hash))
	{
		return 0;
	}
	return _hash->m_numOfItems;
}

size_t HashCapacity(const Hash* _hash)
{
	if(!IS_VALID(_hash))
	{
		return 0;
	}
	return _hash->m_hashSize;
}

double HashAverageRehashes(const Hash* _hash)
{
	if(!IS_VALID(_hash) || !_hash->m_counterOfInsertions)
	{
		return 0;
	}
	/*printf("%lu / %lu\n",_hash->m_allRehashOperations,_hash->m_counterOfInsertions);*/
	return (double)_hash->m_allRehashOperations / _hash->m_counterOfInsertions;
}

size_t HashMaxReHash(const Hash* _hash)
{
	if(!IS_VALID(_hash))
	{
		return 0;
	}
	/*printf("%lu\n",_hash->m_maxOfRehashOperations);*/
	return _hash->m_maxOfRehashOperations;
}

void HashPrint(const Hash* _hash)
{
	size_t i;
	if(!IS_VALID(_hash))
	{
		return;
	}
	for(i=0;i<_hash->m_capacity;i++)
	{
		if(_hash->m_state[i]==INIT)
		{
			printf("I,");
		}
		else if(_hash->m_state[i]==EMPTY)
		{
			printf("E,");
		}
		else
		{
			printf("%d,",_hash->m_data[i]);
		}
	}
	printf("\n");
}



/*----------------------------------static functions---------------------------------------------*/

static int GetNextPrime(size_t _num)
{
	while(!IsPrime(_num))
	{
		_num++;
	}
	return _num;
}


static int IsPrime(size_t _num)
{
	int i;
	float len = sqrt(_num);	
	if(_num==1 || _num==2)
	{
		return 1;	
	}
	if(_num%2==0)
	{
		return 0;
	}
	for(i=3;i<=len;i++)
	{
		if(_num%i==0)
		{
			return 0;		
		}
	}
	return 1;
}

static int IsFound(const Hash* _hash, int _data)
{
	size_t hashVal;
	if(!IS_VALID(_hash))
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	if(_hash->m_numOfItems == 0)
	{
		return 0;
	}

	hashVal = _hash->m_hashF(_data) % _hash->m_capacity;

	if(_hash->m_state[hashVal]==USED && _hash->m_data[hashVal] == _data)
	{
		return 1;
	}
	if(FindRehashIndex(_hash,hashVal,_data)>0)
	{
		return 1;
	}
	return 0;
}

static int FindRehashIndex(const Hash* _hash,size_t _hashVal,int _data)
{
	size_t reHashCount = 0;
	while(_hash->m_state[_hashVal]!=INIT && reHashCount<=_hash->m_maxOfRehashOperations+1)
	{
		if(_hash->m_state[_hashVal]==USED && _hash->m_data[_hashVal] == _data)
		{
			return _hashVal;
		}
		reHashCount++;
		_hashVal++;
		_hashVal %= _hash->m_capacity;
	}
	return -1;
}

static void InsertData(Hash* _hash,size_t _hashVal,int _data)
{
	_hash->m_state[_hashVal] = USED ; 
	_hash->m_data[_hashVal] = _data;
	_hash->m_numOfItems++;
	_hash->m_counterOfInsertions++;
}

