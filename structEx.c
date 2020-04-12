#include<stdio.h>
#define MAX_SIZE 3
#define MAX_NAME_SIZE 10

typedef struct Person
{
	char name[MAX_NAME_SIZE];
	int age;
	int id;

} person;

void PrintPeople(person _people[] ,int _size)
{
	int i;
	for(i=0;i<_size;i++)
	{
		printf("person no %d name:%s age:%d id:%d\n",i+1,_people[i].name,_people[i].age,_people[i].id);
	}
	printf("\n");
}

void SetName(char _toname[] , char *_fromname)
{
	int i=0;
	while(_toname[i]!='\0' || _fromname[i]!='\0')
	{
		_toname[i]=_fromname[i];
		i++;
	}
}

void SetPersonData(person *_person , char* _name , int _age , int _id)
{
	SetName(_person->name,_name);
	_person->age=_age;
	_person->id=_id;
}

void ScanPerson(person *_person)
   
	int age,id;
	char name[MAX_NAME_SIZE];
	printf("please enter name\n");
	scanf("%s",name);
	printf("please enter age\n");
	scanf("%d",&age);
	printf("please enter id\n");  
	SetPersonData(_person,name,age,id);
}

int main()
{
	int i;
	person people[MAX_SIZE];
	for(i=0;i<MAX_SIZE;i++)
	{
		printf("Details of person no:%d\n",i+1);
		ScanPerson(&people[i]);
	}
	PrintPeople(people,MAX_SIZE);
	return 0;
}
