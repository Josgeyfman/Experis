#include<stdio.h>
#include<string.h>
#define MAX_LEN 50

typedef struct Person
{
	char name[MAX_LEN];
	int id;
	int age;
	int edu;
} person;

void SwapPeople(person* _p1,person* _p2)
{
	person tmp = (*_p1);
	*_p1 = (*_p2);
	*_p2 = tmp;

}

void SortByName(person _people[] ,int _len)
{
	int i,j,swapped;
	for(i=0;i<_len-1;i++)
	{
		swapped=0;
		for(j=0;j<_len-i-1;j++)
		{
			if(strcmp(_people[j].name,_people[j+1].name)>0)
			{
				SwapPeople(&_people[j],&_people[j+1]);
				swapped = 1;
			}
		}
		if(!swapped)
		{
			break;

		}
		
	}

}

void SortByID(person _people[] ,int _len)
{
	int i,j,swapped;
	for(i=0;i<_len-1;i++)
	{
		swapped=0;
		for(j=0;j<_len-i-1;j++)
		{
			if(_people[j].id > _people[j+1].id)
			{
				SwapPeople(&_people[j],&_people[j+1]);
				swapped = 1;
			}
		}
		if(!swapped)
		{
			break;

		}
		
	}

}

int IsPrime(int _n)
{
	int i;
	float res;	
	if(_n==1 || _n==2)
	{
		return 1;	
	}
	if(_n%2==0)
	{
		return 0;
	}
	for(i=3;i<_n;i++)
	{
		res = _n/i;
		res = res - (int)res;
		if(res>0)
		{
			return 0;		
		}
	}
	return 1;

}

void ReverseString(char str[])
{
	int size = strlen(str),i=0;
	char curr;
	while(i<size/2)
	{
		curr = str[i];
		str[i] = str[size-i-1];
		str[size-i-1] = curr;
		i++;
	}
}

int IsDigit(char dig)
{
	if(dig>='1' && dig<='9')
	{
		return 1;
	}
	return 0;
}



int MyAtoi(char* str)
{
	int i=0,number=0,currNum,j=0 ,sign=0;		
	int size=1; 
	char numStr[MAX_LEN],tmp;
	
	if(!str)
	{
		return -1;
	}
	
	while(str[i]!='\0' || str[i]!='\0')
	{
		size++;
		i++;
	} 
	i=0;
	while(i<size &&  !IsDigit(str[i]))
	{
		if(str[i]=='-' && IsDigit(str[i+1]))
		{
			sign=1;
		}
		i++;
	}
	printf("i:%d size:%d \n",i,size);
	if(i==size)
	{
		i=0;	
	}
	printf("%d\n",i);
	while(i<size && (IsDigit(str[i]) || str[i]=='0'))
	{
		numStr[j++] = str[i++];
	}
	numStr[j] ='\0';
	size = strlen(numStr);
	j=1;
	while(size-1>=0)
	{
		 tmp = numStr[size-1];	
		currNum = tmp - '0';
		currNum = currNum * j;
		number+=currNum;
		j*=10;
		size--;
	}
	return (sign==1) ? -number : number;
}

void MyItoA(int n ,char* str)
{
	int i=0 ,curr,neg=0;
	if(n<0)
	{
		n=n*(-1);
		neg=1;
	}
	printf("%d n\n",n);
	while(n>0)
	{
		curr = n%10;
		str[i++] = curr + '0';
		n /= 10;
	}
	if(neg)
	{
		str[i++]='-';
		
	}
	str[i]='\0';
	ReverseString(str);
	return;
	
}
void PrintToFile(char* fname,person* people,int size)
{
	int i=0;	
	FILE* fp;
	if(!fname || !people)
	{
		return;
	}
	fp = fopen(fname,"w");
	if(!fp)
	{
		return;
	}
	while(i<size)
	{
		fprintf(fp,"%-5s %-5d %-5d %-5d\n", people[i].name,people[i].id,people[i].age,people[i].edu);
		i++;
	}
	fclose(fp);
	return;
}

void ReadFromFile(char* fname)
{
	int id,age,edu;	
	char name[MAX_LEN];
	FILE* fp;
	if(!fname)
	{
		return;
	}
	fp = fopen(fname,"r");
	if(!fp)
	{
		return;
	}
	printf("name	id	age	edu  read txt\n");
	while(!feof(fp))
	{
		fscanf(fp,"%s %d %d %d\n", name,&id,&age,&edu);
		printf("%s\t%d\t%d\t%d\t\n",name,id,age,edu);
	}
	fclose(fp);
	return;
}

void PrintToFileDirect(char* fname,person* people,int size)
{
	FILE* fp;
	if(!fname || !people)
	{
		return;
	}
	fp = fopen(fname,"w");
	if(!fp)
	{
		return;
	}
	fwrite(people,sizeof(person),size,fp);
	fclose(fp);
	return;
}

void ReadFromFileDirect(char* fname, int size)
{
	int i=0;	
	person people[5];
	FILE* fp;
	if(!fname)
	{
		return;
	}
	fp = fopen(fname,"r");
	if(!fp)
	{
		return;
	}
	printf("name	id	age	edu  read direct\n");
	fread(people,sizeof(person),size,fp);
	while(i<size)
	{
		printf("%s\t%d\t%d\t%d\t\n",people[i].name,people[i].id,people[i].age,people[i].edu);
		i++;
	}
	fclose(fp);
	return;
}

int main()
{
	
	/*char number[MAX_LEN];
	int num;
	printf("please enter a number \n");
	scanf("%d", &num);
	MyItoA(num,number);
	printf("the string is \"%s\"\n", number);
	*/
	/*printf("please enter a string\n");
	scanf("%s", number);
	num=MyAtoi(number);
	printf("the number is %d\n", num);*/
	int i;
	char* names[] ={"A","B","C","D","E"};
	char fname[MAX_LEN]="people.txt";
	char fname1[MAX_LEN]="peoplebin.txt";
	person people[5];
	for(i=0;i<5;i++)
	{
		strcpy(people[i].name, names[i]);
		people[i].id = 4-i;
		people[i].age=i;
		people[i].edu=i;
	}
	
	PrintToFile(fname,people,5);
	ReadFromFile(fname);
	PrintToFileDirect(fname1,people,5);
	ReadFromFileDirect(fname1,5);
	return 0;
}







