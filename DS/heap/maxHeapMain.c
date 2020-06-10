#include<stdio.h>
#include"max_heap.h"
#include"vector.h"

enum {CREATE=1,INSERT,HMAX,EXMAX,NITEMS,PRINT,DESTROY,EXIT};

int main()
{
	size_t size=0,command,exit=0;
	int data;
	heap* heap;
	vector* vec;
	ERRCODE res;
	do
	{	
		printf("\nPlease enter command:\nCreate Max Heap: 1\nInsert: 2\nHeap Max: 3");
		printf("\nExtract Max: 4\nNumber of items: 5\nPrint: 6\nDestroy Heap: 7\nExit: 8\n");
		scanf("%lu",&command);
		switch(command)
		{
			 case CREATE:  	printf("Please enter Heap size\n");
					scanf("%lu",&size);
					vec = VectorCreate(size,3);
					while(size--)
					{
						VectorAddTail(vec,rand()%100);	
					}
					heap = HeapBuild(vec);
					if(heap)
					{
						printf("Heap created\n");
					}
					else
					{
						printf("Error Creating Heap\n");
					}
					break;

		         case INSERT: 	printf("Please enter data to insert\n");
					scanf("%d",&data);
					res = HeapInsert(heap,data);
					if(res==ERR_SUCCESS)
					{
						printf("Inserted %d to Heap\n" ,data);
					}
					else
					{
						printf("Failed to insert\n");
					}
					break;

			case HMAX: 	res = HeapMax(heap,&data);
					if(res==ERR_SUCCESS)
					{
						printf("Heap Max is %d\n" ,data);
					}
					else
					{
						printf("Error retrieving Max\n");
					}
					break;
	
			case EXMAX: 	res = HeapExtractMax(heap,&data);
					if(res==ERR_SUCCESS)
					{
						printf("Heap Max extracted successfully %d\n" ,data);
					}
					else
					{
						printf("Error extracting Max\n");
					}
					break;

			 case NITEMS: 	data = HeapItemsNum(heap);
					if(data >=0)
					{
						printf("Number of items is %d \n" ,data);
					}
					else 
					{
						printf("inavlid input\n" );
					}
					break;

		       	   case PRINT:  HeapPrint(heap);
					break;
					
		         case DESTROY:	if(heap!=NULL)
					{
						HeapDestroy(heap);
						VectorDestroy(vec);
						heap=NULL;
						printf("Destroy result: success\n");
						break;
					}
					else
					{
						printf("Destroy result: nothing to destroy\n");
					}
					break;
	
			    case EXIT:  exit=1; 
					break;
		}
		
	}while(!exit);
	
	if(heap)
	{
		HeapDestroy(heap);
		VectorDestroy(vec);
		heap=NULL;
	}
	return 0;
}
