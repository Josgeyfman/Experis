#include<stdio.h>

int Mul(int a,int b){
	return a*b;
}

int Sum(int a,int b){
	return a+b;
}

int Sub(int a,int b){
	return a-b;
}

int main(){
	int a=5,b=4;
	printf("%d + %d = %d\n",a,b,Sum(a,b));
	printf("%d * %d = %d\n",a,b,Mul(a,b));
	printf("%d - %d = %d\n",a,b,Sub(a,b));
	return 0;
}



