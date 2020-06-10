#include"vector.h"

enum {CREATE=1,PUSH,FIND,POP,PRINT,POP_INDEX,FIND_MAX ,SORT,GET,SET,DESTROY,EXIT};


size_t GetVectorSize(vectorp _vecPtr)
{
	size_t size=0;
	int temp;
	if(_vecPtr!=NULL)
	{
		while(VectorGet(_vecPtr,++size,&temp)!=ERR_INDEX);
	}
	return size;
}

ERRCODE FindMax(vectorp _vecPtr ,int* _max)
{
	size_t i=1 ;
	int temp;
	ERRCODE res;

	if((res = VectorGet(_vecPtr,i,_max)) !=ERR_SUCCESS)
	{
		return res;
	}

	while((res = VectorGet(_vecPtr,i++,&temp))==ERR_SUCCESS)	
	{
		if(temp > *_max)
		{
			*_max = temp;
		}
	}

	return ERR_SUCCESS ;
}

typedef struct pair {

	size_t  m_indx;
	int	m_data;

}  pair_t;

static void Swap(vectorp _vecPtr,pair_t* _first,pair_t* _second )
{
	VectorSet(_vecPtr,_first->m_indx, _second->m_data);
	VectorSet(_vecPtr,_second->m_indx, _first->m_data);
}


void BubbleSortVector(vectorp _vecPtr)
{
	int swapped=1;
	size_t size;
	pair_t first;
	pair_t next ;

	first.m_indx = 1;
	next.m_indx = first.m_indx+1;
 	
	size = VectorNumOfElements(_vecPtr);

	while(size-- && swapped)
	{
		first.m_indx = 1;
		next.m_indx = first.m_indx+1;
		swapped=0;
		while(first.m_indx<=size)
		{
			VectorGet(_vecPtr,first.m_indx,&first.m_data);
			VectorGet(_vecPtr,next.m_indx,&next.m_data);
			if(first.m_data > next.m_data)
			{
				Swap(_vecPtr,&first,&next);
				swapped=1;
			}
			
			first.m_indx = next.m_indx++;
		}
		
	}
}

size_t  VectorFind(vectorp _vecPtr ,int _data)
{
	size_t i=1 ;
	int temp;
	ERRCODE res;

	if((res = VectorGet(_vecPtr,i,&temp)) !=ERR_SUCCESS)
	{
		return res;
	}

	while((res = VectorGet(_vecPtr,i++,&temp))==ERR_SUCCESS)	
	{
		if(temp == _data)
		{
			return i;
		}
	}

	return 0;
}

int main()
{
	size_t  size,blockSize,index;	
	int    	command,data,remData,exit=0;
	vectorp vecPtr = NULL;
	ERRCODE result;
	do
	{	
		printf("\nPlease enter command:\nCreate Vector: 1\nPush to tail: 2\nFind value: 3");
		printf("\nPop from tail: 4\nPrint vector: 5\nRemove at index: 6");
		printf("\nFind max: 7\nBubble sort: 8\nGet value: 9\nSet value: 10\nDestroy vector: 11\nExit: 12\n");
		scanf("%d",&command);
		switch(command)
		{
			
			case CREATE:	if(vecPtr!=NULL)
					{
						
						printf("Create result: Vector exists, please destroy it first\n");
					}
					else
					{
						printf("Please enter initial size:\n");
						scanf("%lu",&size);
						printf("Please enter blockSize:\n");
						scanf("%lu",&blockSize);
						if(size<1 && blockSize < 1){
							printf("Create result: ERR_ILLEGAL_INPUT\n");
							break;
						}
						vecPtr = VectorCreate(size,blockSize);
						if(vecPtr==NULL)
						{
							printf("\nCreate result: ERR_MEM_ALLOC\n");
							break;
						}
						printf("\nCreate result: Vector created\n");
					}
					break;
	
		        case PUSH: 	printf("Please enter value to insert:\n");
					scanf("%d",&data);
					result = VectorAddTail(vecPtr,data);
					printf("Insert result: ");					
					PrintERRCODE(result);
					break;
			
			case FIND:      printf("Please enter the value to be found:\n");
					scanf("%d",&data);
					result = VectorFind(vecPtr,data);
					printf("Find result: ");
					if(result>0)
					{
						printf("The index of the value is: %d\n" ,result);
					}
					else
					{
						printf("not found or error finding element\n");			
					}
					break;
			
		
		  	 case POP:  	result = VectorRemoveTail(vecPtr,&data);
					if(result==ERR_SUCCESS)
					{
						printf("The value popped is: %d\n" ,data);
					}
					printf("Remove result: ");
					PrintERRCODE(result);
					break;
			
		       case PRINT:      result = VectorPrint(vecPtr);
					printf("Print result: ");
					if(result>0)
					{
						printf("ERR_SUCCESS printed %d values\n", result);
					}
					else
					{
						PrintERRCODE(result);
					}	
					break;
	
		   case POP_INDEX:	printf("Please enter the index to get from:\n");
					scanf("%lu",&index);
					
					result = VectorGet(vecPtr,index,&remData);
					VectorRemoveTail(vecPtr,&data);
					VectorSet(vecPtr,index,data);
					if(result==ERR_SUCCESS)
					{
						printf("The value retrieved is: %d\n" ,remData);
					}
					printf("Remove at index result: ");
					PrintERRCODE(result);
					break;
			case FIND_MAX:  result = FindMax(vecPtr,&data);
					if(result==ERR_SUCCESS)
					{
						printf("The max is: %d\n" ,data);
					}
					printf("max result: ");
					PrintERRCODE(result);
					break;

			 case SORT:	printf("before sort :\n");
					VectorPrint(vecPtr);
					BubbleSortVector(vecPtr);
					printf("after sort :\n");
					VectorPrint(vecPtr);
					break;
	
			 case GET:	printf("Please enter the index to get from:\n");
					scanf("%lu",&index);
					result = VectorGet(vecPtr,index,&data);
					if(result==ERR_SUCCESS)
					{
						printf("The value retrieved is: %d\n" ,data);
					}
					printf("GET result: ");
					PrintERRCODE(result);
					break;	
			
			case SET:	printf("Please enter the index to set to:\n");
					scanf("%lu",&index);
					printf("Please enter value to insert:\n");
					scanf("%d",&data);
					result = VectorSet(vecPtr,index,data);
					printf("SET result: ");
					PrintERRCODE(result);
					break;

		      case DESTROY:	if(vecPtr!=NULL)
					{
						VectorDestroy(vecPtr);
						vecPtr=NULL;
						printf("Destroy result: ERR_SUCCESS\n");
						break;
					}
					else
					{
						printf("Destroy result: ERR_ILLEGAL_INPUT\n");
					}
					break;
	
			  case EXIT:	exit=1; 
					break;
	
		}
		
	}while(!exit);
	
	if(vecPtr!=NULL)
	{
		VectorDestroy(vecPtr);
		vecPtr=NULL;
	}
	
	return 0;
}
