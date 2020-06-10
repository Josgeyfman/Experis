#ifndef _FUNCBSORT_H_
#define _FUNCBSORT_H_

int Bigger(int _a,int _b);

int Smaller(int _a,int _b);

int Even(int _a,int _b);

int Odd(int _a,int _b);

void BubbleSort(int arr[],int size , int (*f)(int,int));

#endif /*_FUNCBSORT_H_*/
