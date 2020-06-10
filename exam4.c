/*----------------------Question 1 ------------------*/
A.
#define CHAR_VALUES 256
int IsAnagram(char* _str,char* _str2)
{
	register int size,i;
	int arr1[CHAR_VALUES],arr2[CHAR_VALUES];
	if(!_str1 || !str2)
	{
		return;
	}
	size = strlen(_str1);
	if(strlen(_str2)!=size)
	{
		return 0;
	}
	for(i=0;i<size;i++)
	{
		arr1[i]=0;
		arr2[i]=0;
	}
	for(i=0;i<size;i++)
	{
		arr1[str1[i]]++;
		arr2[str2[i]]++;
	}
	for(i=0;i<_range;i++)
	{
		if(arr1[i]!=arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

B. time comlexity O(n) where n is the length of the strings. since we pass over the strings one time;
C. space complexity i O(1) , since we use  2 arrays of a constant length.

/*----------------------Question 2 ------------------*/

Node* Flip(Node* _node)
{
	node* rev;
	if(!_node)
	{
		return;
	}
	if(!_node->next)
	{
		return node;
	}
	rev = Flip(node->next);
	node->next->next= node;
	node->next=NULL;
	return rev;
}

/*----------------------Question 3 ------------------*/

		space    average 	Worst  		stable
BubbleSort 	O(1)   	 O(n^2) 	O(n^2)		yes
SelectionSort 	O(1) 	 O(n^2) 	O(n^2)		yes
QuickSort 	O(1)  	 O(nlogn)	O(n^2)		no
CountingSort 	O(n)     O(n)	 	O(n)		useally no but can be implemented as stable
MergrSort 	O(n)     O(nlogn)	O(nlogn)	yes

/*----------------------Question 4 ------------------*/

A.
int IsBinarySearchTree(struct Tree* _root)
{
	int left,right;
	if(!root)
	{
		return 1;
	}
	left = IsBinarySearchTree(_root->left);
	right = IsBinarySearchTree(_root->left);
	if(!left || !right)
	{
		return 0;
	}
	if(_root->left->data > _root->data || _root->right->data < _root->data )
	{
		return 0;
	}
	return 1;
}

B. time comlexity O(n) . since we pass over all nodes in the tree one time;
C. space complexity i O(1) , no additional space used.

/*----------------------Question 5 ------------------*/

int LCA(struct Tree* _root,int _a,int _b)
{
	int tmp;
	if(_a >_b)
	{
		tmp =_a;
		_a = _b;
		_b = tmp;
	}
	if(root->data >_b)
	{
		return LCA(_root->left,_a,_b);
	}
	if(root->data<_a)
	{
		return LCA(_root->left,_a,_b);
	}
	return root->data;
}

/*----------------------Question 6 ------------------*/

void MirrorTree(Tree* _root)
{
	node* tmp;
	if(!root)
	{
		return;
	}
	MirrorTree(_root->left);
	MirrorTree(_root->left);
	tmp = _root->left;
	_root->left=_root->right;
	_root->right = tmp;
}

B. space complexity i O(1) , no additional space used.

B. average time comlexity O(n) . since we pass over all nodes in the tree time;

D. worst time comlexity O(n) . since we pass over all nodes in the tree time;

/*----------------------Question 7 ------------------*/

A.
void HeapSort(Vector* _vec)
{
	Heap* heap;
	int last,max;
	if(_vec)
	{
		return;
	}
	heap = HeapBuild(_vec);
	if(!heap)
	{
		return;
	}
	while(heap->m_nheapSize>0)
	{
		VectorGet(heap->m_vector,heap->m_nheapSize,&last);
		HeapMax(heap,&max);
		VectorSet(heap->m_vector,heap->m_nheapSize,max);
		VectorSet(heap->m_vector,1,last);
		heap->m_nheapSize--;
		HeapifyDown(heap->m_vector,1);
	}
	HeapDestroy(heap);
}

B. time complexity is O(nlogn) ,  because we extract max which is O(logn) operation for every node in the heap (n*logn)

