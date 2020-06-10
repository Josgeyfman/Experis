#include<stdio.h>
#include"bst.h"

enum {CREATE=1,INSERT,ISFOUND,ISFULL,LEVEL,SIMILIAR,PERFECT,MIRROR,PREPRINT,INPRINT,POSTPRINT,DESTROY,EXIT};

int main()
{
	size_t command,exit=0;
	int data;
	tree* treep;
	tree* treep1 =TreeCreate();
	ERRCODE res;
	do
	{	
		printf("\nPlease enter command:\nCreate bst: 1\nInsert: 2\nis found: 3");
		printf("\nIs full: 4\nTree level: 5\nsimilar: 6\nPerfect: 7\nMirror: 8");
		printf("\nPre-order print: 9\nIn-order print: 10\nPost-order print: 11\nDestroy bst: 12\nExit: 13\n");		
		scanf("%lu",&command);
		switch(command)
		{
			 case CREATE:   treep =TreeCreate();
					if(treep)
					{
						printf("Bst created\n");
					}
					else
					{
						printf("Error Creating Bst\n");
					}
					break;

		         case INSERT: 	printf("Please enter data to insert\n");
					scanf("%d",&data);
					res = TreeInsert(treep,data);
					if(res==ERR_SUCCESS)
					{
						printf("Inserted %d to Bst\n" ,data);
					}
					else
					{
						printf("Failed to add\n");
					}
					break;

			case ISFOUND: 	printf("Please enter data to check\n");
					scanf("%d",&data);
					if(TreeIsDataFound(treep,data))
					{
						printf("%d is in the Bst\n" ,data);
					}
					else
					{
						printf("%d is not  in the Bst\n" ,data);
					}
					break;
	
			case ISFULL: 	data = TreeIsFull(treep);
					if(data==1)
					{
						printf("tree is full\n" );
					}
					else if(data==0)
					{
						printf("tree is not full\n" );
					}
					else 
					{
						printf("inavlid input\n" );
					}
					break;

			 case LEVEL: 	data = TreeLevel(treep);
					printf("tree level is %d \n" ,data);
					if(data >-1)
					{
						printf("tree level is %d \n" ,data);
					}
					else 
					{
						printf("inavlid input or empty tree\n" );
					}
					break;

			case SIMILIAR: 	TreeInsert(treep1,4);
					TreeInsert(treep1,2);
					TreeInsert(treep1,3);
					TreeInsert(treep1,5);
					data = TreesAreSimilar(treep,treep1);
					if(data==1)
					{
						printf("trees are similar\n" );
					}
					else if(data==0)
					{
						printf("trees are not similar\n" );
					}
					else 
					{
						printf("inavlid input\n" );
					}
					break;
	
			case PERFECT: 	data = TreeIsPerfect(treep);
					if(data==1)
					{
						printf("tree is perfect\n" );
					}
					else if(data==0)
					{
						printf("tree is not perfect\n" );
					}
					else 
					{
						printf("inavlid input\n" );
					}
					break;

			 case MIRROR:	treep = TreeMirror(treep);
					if(treep)
					{
						printf("tree mirrored\n" );
					}
					else
					{
						printf("error in mirror tree\n" );
					}
					break;

		  	case PREPRINT:  TreePrint(treep,PRE_ORDER);
					TreePrettyPrint(treep);
					break;

			 case INPRINT:  TreePrint(treep,IN_ORDER);
					TreePrettyPrint(treep);
					break;
			
		       case POSTPRINT:  TreePrint(treep,POST_ORDER);
					TreePrettyPrint(treep);
					break;
					
		         case DESTROY:	if(treep!=NULL)
					{
						TreeDestroy(treep);
						treep=NULL;
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
	
	TreeDestroy(treep1);
	if(treep)
	{
		TreeDestroy(treep);
		treep=NULL;
	}
	return 0;
}

