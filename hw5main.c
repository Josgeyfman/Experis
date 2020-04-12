#include<stdio.h>
#include"hw5.h"
#define INSERT 1
#define DELETE 2
#define BLOCK_SIZE_CHANGE 3
#define EXIT 4



int main()
{
	int *ptr ,data,size,numOfelements,blockSize,deletedData,command,tmp,exit=0; 
	printf("please enter size:\n");
	scanf("%d",&size);
	printf("please enter blockSize:\n");
	scanf("%d",&blockSize);
	if(size<1 || blockSize < 1){
		printf("bad input action failed\n");
		return -1;
	}
	ptr = DynamicArrayCreate(size);
	
	if(ptr==NULL)
	{
		printf("\nmemory allocation error\n");
		return -1;
	}
	printf("\narray created ");
	printf("array size: %d, num of elements: %d, block size: %d\n",size,numOfelements,blockSize);
	do
	{	
		printf("\nplease enter Command:\nInsert: 1\nDelete: 2\nChange Block size: 3\nExit: 4\n");
		scanf("%d",&command);
		switch(command)
		{
			case INSERT: 	printf("please enter data:\n");
					scanf("%d",&data);
					printf("\nbefore insert ");
					printf("size: %d, num of elements: %d, block size: %d\n",size,numOfelements,blockSize);
					PrintPtrArr(ptr,numOfelements);
					
					if(DynamicArrayInsert(&ptr,data,&size,&numOfelements,blockSize))
					{
						printf("\nerror insering element\n");
						break;
					}
					
					printf("\nafter insert ");
					printf("size: %d, num of elements: %d, block size: %d\n",size,numOfelements,blockSize);
					PrintPtrArr(ptr,numOfelements);
					break;
				
			case DELETE:  	printf("\nbefore delete ");
					printf("size: %d, num of elements: %d, block size: %d\n",size,numOfelements,blockSize);
					PrintPtrArr(ptr,numOfelements);
					
					DynamicArrayDelete(ptr,&deletedData,&numOfelements);
		
					printf("\nafter delete ");
					printf("size: %d, num of elements: %d, block size: %d\n",size,numOfelements,blockSize);
					printf("deletedData: %d\n", deletedData);
					PrintPtrArr(ptr,numOfelements);
					break;
			
	     case BLOCK_SIZE_CHANGE:    tmp = blockSize;
				        printf("please enter blockSize:\n");
					scanf("%d",&blockSize);
					if(blockSize<1)	
					{
						blockSize=tmp;
						printf("bad input action failed\n");
					}
					printf("\nafter change block size ");
					printf("size: %d, num of elements: %d, block size: %d\n",size,numOfelements,blockSize);
						break;
						
			  case EXIT:	exit=1;
					break;
			
		}
		
	}while(!exit);
		
	DynamicArrayDestroy(ptr);
	ptr=NULL;

	return 0;
}
