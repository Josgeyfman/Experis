#include<stdio.h>
#include<unistd.h>
int g_var=0;

int main()
{
	int l_var=0;
	int n,i;
	sleep(10);
	n = fork();
	sleep(4);
	if(n>0)
	{
		for(i=0;i<30;i++)
		{
			printf("father: l %d g %d\n" , ++l_var,++g_var);
			sleep(1);
		}
	}
	else
	{
		for(i=0;i<10;i++)
		{
			printf("son: l %d g %d\n" , --l_var,--g_var);
			sleep(1);
		}
	}
	return 0;
}
