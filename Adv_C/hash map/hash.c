#include <stdlib.h> 		/*allocation*/
#include <math.h>   		/*sqrt*/
#include "list.h"		/*List_Create/Destroy*/
#include "list_functions.h"     /*List_ForEach*/
#include "iterator.h"		/*ListItr_Begin/End*/
#include "hashMap.h"
#define MAGIC_NUM 0xadadfdfd
#define NOT_MAGIC_NUM 0xbeafdada
#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)

struct HashMap
{
	size_t m_magicNum;
	List** m_data;
	size_t m_capacity; 		    /*real hush size */
	size_t m_numOfItems; 		   /*number of key-value pairs in map*/
	HashFunction m_hashF;
	EqualityFunction m_equalF;
};

typedef struct Node
{
	void* m_key;
	void* m_val;
}Node;

typedef void* (*GetFunction)(void*);
typedef Map_Result (*initFunction)(List**,size_t);
typedef Map_Result (*insertFunction)(List*,void*);

typedef struct Context
{
	void*  m_userContext;
	size_t m_runTimes;
	size_t m_cap;
	List** m_newData;
	KeyValueActionFunction m_userAct;
	DestroyFunction m_userKeyDes;
	DestroyFunction m_userValDes;
	GetFunction m_getKey;
	GetFunction m_getVal;
	EqualityFunction eqaul;
	initFunction m_initList;
	insertFunction m_insertData;
	HashFunction m_hashF;
} context;

/*----------------------------------static function signatures----------------------------------*/

static int IsPrime(size_t _num);
static int GetNextPrime(size_t _num);
static ListItr FindInMap(const HashMap* _map, const void* _key);
static ListItr FindIndexInList(List* _list,const void* _key,EqualityFunction _Equal);
static Node* CreateData(const void* _key,const void* _val);
static Map_Result InitList(List** _data,size_t _hval);
static Map_Result InsertData(List* listp,void* _data);
static void* GetKey(ListItr _node);
static void* GetVal(ListItr _node);
static void FreeAllLists(HashMap* _map,context* _con);
static int Map_ActionData(void* _element, void* _context);
static int Map_DestroyData(void* _element, void* _context);
static int Map_EqualData(void* _element, void* _context);
static int Map_RehashData(void* _element, void* _context);
static void GetStats(const HashMap* _map,size_t* _cNum,size_t* _mChain);

/*----------------------------------API functions -----------------------------------------------*/

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hashp = NULL;

	if(!_keysEqualFunc || !_hashFunc || _capacity==0)
	{
		return hashp;
	}

	hashp = (HashMap*)malloc(sizeof(HashMap));
	if(!hashp)
	{
		return hashp;
	}

	hashp->m_capacity = GetNextPrime(_capacity);

	hashp->m_data= (List**)calloc(hashp->m_capacity,sizeof(List*));
	if(!hashp->m_data)
	{
		free(hashp);
		return NULL;
	}

	hashp->m_numOfItems = 0;
	hashp->m_hashF = _hashFunc;
	hashp->m_equalF = _keysEqualFunc;
	hashp->m_magicNum = MAGIC_NUM;

	return hashp;
}


void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	context* mapCon;
	if(!IS_VALID((*_map)))
	{
		return;
	}
	mapCon = (context*)malloc(sizeof(context));
	if(!mapCon)
	{
		return;
	}

	(*_map)->m_magicNum = NOT_MAGIC_NUM;
	mapCon->m_userKeyDes = _keyDestroy;
	mapCon->m_userValDes = _valDestroy;
	mapCon->m_getKey = GetKey;
	mapCon->m_getVal = GetVal;
	FreeAllLists(*_map,mapCon);
	free((*_map)->m_data);
	free(*_map);
	free(mapCon);

	*_map = NULL;
}


Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
	size_t hashVal;
	Node* data;
	Map_Result res;
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	if(!_key)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if(FindInMap(_map,_key))
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}

	data = CreateData(_key,_value);
	if(!data)
	{
		return MAP_ALLOCATION_ERROR;
	}

	hashVal = _map->m_hashF((void*)_key) % _map->m_capacity;

	if(!_map->m_data[hashVal])
	{
		res = InitList(_map->m_data,hashVal);
		if(res!=MAP_SUCCESS)
		{
			return res;
		}
	}
	
	res = InsertData(_map->m_data[hashVal],data);
	if(res!=MAP_SUCCESS)
	{
		return res;
	}
	_map->m_numOfItems++;
	return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{	
	ListItr found;
	Node* element;
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(!_key)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if(_map->m_numOfItems == 0)
	{
		return MAP_EMPTY_ERROR;
	}

	found = FindInMap(_map,_key);
	if(!found)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	element = ListItr_Get(found);
	*_pValue = GetVal(element);

 	return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ListItr found;
	Node* node;
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(!_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if(_map->m_numOfItems == 0)
	{
		return MAP_EMPTY_ERROR;
	}
	
	found = FindInMap(_map,_searchKey);
	if(!found)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	node = ListItr_Remove(found);
	
	*_pValue = GetVal(node);
	*_pKey = GetKey(node);
	
	Map_DestroyData(node,NULL);
	_map->m_numOfItems--;

	return MAP_SUCCESS;
}


size_t HashMap_Size(const HashMap* _map)
{
	if(!IS_VALID(_map))
	{
		return 0;
	}
	return _map->m_numOfItems;
}


Map_Result HashMap_Rehash(HashMap* _map, size_t newCapacity)
{
	
	List* currList = NULL;
	ListItr begin ,end;
	List** newData = NULL;
	size_t i, newCap;
        context* mapCon;
	if(!IS_VALID(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	if(newCapacity==0)
	{
		return MAP_SUCCESS;
	}

	newCap = GetNextPrime(newCapacity);
	newData = (List**)calloc(newCap,sizeof(List*));
	if(!newData)
	{
		return MAP_ALLOCATION_ERROR;
	}

	mapCon = (context*)malloc(sizeof(context));
	if(!mapCon)
	{
		return 0;
	}

	mapCon->m_getKey = GetKey; 		/*set get key func*/
	mapCon->m_initList = InitList;		/*set init list func*/
	mapCon->m_insertData = InsertData;	/*set insert to list func*/
	mapCon->m_newData = newData;		/*set new data*/
	mapCon->m_hashF = _map->m_hashF;	/*set hash func*/
	mapCon->m_cap = newCap;			/*set new capacity*/

	for(i=0;i<_map->m_capacity;i++)
	{
		currList = _map->m_data[i];
		if(currList)
		{
			begin = ListItr_Begin(currList);
			end =  ListItr_End(currList);
			mapCon->m_runTimes = List_Size(currList);
			ListItr_ForEach(begin,end,Map_RehashData,mapCon);
			List_Destroy(&currList,NULL);
		}
	}
	_map->m_capacity = newCap;
	free(_map->m_data);
	_map->m_data = newData;
	free(mapCon);
	return MAP_SUCCESS;
}


size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t i,count=0,runTimes=0;
	List* currList = NULL;
	ListItr begin,end;
	context* mapCon;

	if(!IS_VALID(_map) || !_action)
	{
		return 0;
	}

	mapCon = (context*)malloc(sizeof(context));
	if(!mapCon)
	{
		return 0;
	}

	mapCon->m_userContext = _context;
	mapCon->m_userAct = _action;

	for(i=0;i<_map->m_capacity;i++)
	{
		currList = _map->m_data[i];
		if(currList)
		{
			runTimes = List_Size(currList);
			mapCon->m_runTimes = runTimes;
			begin = ListItr_Begin(currList);
			end = ListItr_End(currList);
			ListItr_ForEach(begin,end,Map_ActionData,mapCon);
			count+= runTimes - mapCon->m_runTimes;
		}
	}
	free(mapCon);
	return count;
}

Map_Stats HashMap_GetStatistics(const HashMap* _map)
{
	size_t chainNum=0,maxChain=0;
	Map_Stats stats ={0,0,0,0};
	if(!IS_VALID(_map))
	{
		return stats;
	}
	GetStats(_map,&chainNum,&maxChain);
	stats.numberOfBuckets=_map->m_capacity;
	stats.numberOfChains=chainNum;
	stats.maxChainLength=maxChain;
	if(chainNum>0)
	{
		stats.averageChainLength=_map->m_numOfItems/chainNum;
	}
	else
	{	
		stats.averageChainLength = 0;
	}
	return stats;
}

/*----------------------------------static functions---------------------------------------------*/

static void GetStats(const HashMap* _map,size_t* _cNum,size_t* _mChain)
{
	size_t i,listSize;
	
	for(i=0;i<_map->m_capacity;i++)
	{
		if(_map->m_data[i])
		{
			(*_cNum)++;
			listSize = List_Size(_map->m_data[i]);
			if(listSize>*_mChain)
			{
				*_mChain=listSize;	
			}
		}
	}

}

static int Map_ActionData(void* _element, void* _context)
{
	void* key=NULL;
	void* val=NULL;
	context* con = (context*) _context;
	if(!_element || !_context)
	{
		return 0;
	}
	key = GetKey(_element) ;
	val = GetVal(_element) ;
	if(!con->m_userAct(key,val,con->m_userContext))
	{
		return 0;
	}
	con->m_runTimes--;
	return con->m_runTimes;
}

static int Map_DestroyData(void* _element, void* _context)
{
	void* key=NULL;
	void* val=NULL;
	context* con = (context*) _context;
	if(con)
	{
		key = con->m_getKey(_element);
		val = con->m_getVal(_element);
		if(con->m_userKeyDes)
		{
			con->m_userKeyDes(key);
		}
		if(con->m_userValDes &&  val)
		{
			con->m_userValDes(val);
		}
		free(_element);
		con->m_runTimes--;
		return con->m_runTimes;
	}
	free(_element);
	return 0;
}

static int Map_RehashData(void* _element, void* _context)
{
	void* key=NULL;
	size_t hval;
	Map_Result res;
	context* con = (context*) _context;

	key = con->m_getKey(_element);

	hval = con->m_hashF((void*)key) % con->m_cap;

	if(!con->m_newData[hval])
	{
		res = con->m_initList(con->m_newData,hval);
		if(res!=MAP_SUCCESS)
		{
			return 0;
		}
	}
	res  = con->m_insertData(con->m_newData[hval],_element);
	if(res!=MAP_SUCCESS)
	{
			return 0;
	}
	con->m_runTimes--;
	return con->m_runTimes;
}

static int Map_EqualData(void* _element, void* _context)
{
	void* key=NULL;
	context* con = (context*) _context;
	key = con->m_getKey((void*)_element) ;
	return con->eqaul(key,con->m_userContext);
}

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

static ListItr FindInMap(const HashMap* _map, const void* _key)
{
	size_t hval;
	if(_map->m_numOfItems == 0)
	{
		return NULL;
	}

	hval = _map->m_hashF((void*)_key) % _map->m_capacity;

	if(!_map->m_data[hval])
	{
		return NULL;
	}

	return FindIndexInList(_map->m_data[hval],_key,_map->m_equalF);
}

static ListItr FindIndexInList(List* _list,const void* _key,EqualityFunction _Equal)
{
	ListItr begin,end;
	context* mapCon;
	mapCon = (context*)malloc(sizeof(context));
	if(!mapCon)
	{
		return 0;
	}
	mapCon->m_getKey	= GetKey;
	mapCon->eqaul	= _Equal;
	mapCon->m_userContext = (void*)_key;

	begin = ListItr_Begin(_list);
	end = ListItr_End(_list);

	begin = ListItr_FindFirst(begin,end,Map_EqualData,mapCon);
	if(!ListItr_Equals(begin,end))
	{
		free(mapCon);
		return begin;
	}

	free(mapCon);
	return NULL;
	
}


static Map_Result InsertData(List* listp,void* _data)
{
		
		if(LIST_ALLOCATION_ERROR == List_PushTail(listp,_data))
		{
			return MAP_ALLOCATION_ERROR;
		}
		
		return MAP_SUCCESS;
}

static Map_Result InitList(List** _data,size_t _hval)
{
		List* listp = List_Create();
		if(!listp)
		{
			return MAP_ALLOCATION_ERROR;
		}
		_data[_hval] = listp;
		return MAP_SUCCESS;
}

static void FreeAllLists(HashMap* _map,context* _con)
{
	size_t i;
	List* currList =NULL;
	ListItr begin,end;
	for(i=0;i<_map->m_capacity;i++)
	{
		currList =_map->m_data[i];
		if(currList)
		{
			begin = ListItr_Begin(currList);
			end = ListItr_End(currList);
			_con->m_runTimes = List_Size(currList);
			ListItr_ForEach(begin,end,Map_DestroyData,_con);
			List_Destroy(&currList,NULL);
		}
	}
}

static Node* CreateData(const void* _key,const void* _val)
{
		Node* node = (Node*)malloc(sizeof(Node));
		if(!node)
		{
			return NULL;
		}
		node->m_key = (void*)_key;
		node->m_val = (void*)_val;
		return node;
}	

static void* GetVal(ListItr _node)
{
		return ((Node*)_node)->m_val;
}

static void* GetKey(ListItr _node)
{
		return ((Node*)_node)->m_key;
}

