/*---------------------FINAL EXAM C ----------------*/

/*----------------------Q1-------------------------*/
char* strncpy(char* str1 ,const char* str2,size_t n)
{
	int size1,size2,i=0;
	if(!str1 || !str2)
	{
		return str1;

	}
	size1 = strlen(str1);
	size2 = strlen(str2);
	if(n>size2 || n>size1)
	{
		return str1;
	}
	while(i<n)
	{
		str1[i++] = str2[i];
	}
	str1[i]='\0';
	return str1;
}

char* strncat(char* str1 ,const char* str2,size_t n)
{
	int size1,size2,i=0;
	if(!str1 || !str2)
	{
		return str1;

	}
	size1 = strlen(str1);
	size2 = strlen(str2);
	if(n+size2 > size1)
	{
		return str1;
	}
	while(i<n)
	{
		str1[size1 + i] = str2[i];
		i++;
	}
	str1[i]='\0';
	return str1;
}

int strncmp(const char* str1 ,const char* str2,size_t n)
{
	int size1,size2,i=0;
	if(!str1 || !str2)
	{
		return str1;

	}
	size1 = strlen(str1);
	size2 = strlen(str2);
	if(n>size2 || n>size1)
	{
		return str1;
	}
	while(i<n)
	{
		if(str1[i] < str2[i])
		{
			return 1;
		}
		if(str1[i] > str2[i])
		{
			return -1;
		}
		i++;
	}
	return 0;
}

/*----------------------Q2-------------------------*/
int strIndex(const char* _str1,const char* _str2)
{
	const char* curr = _str1;
	int size1,size2;
	if(!_str1 || !_str2)
	{
		return -1;
	}
	size1 = strlen(_str1);
	size2 = strlen(_str2);
	while(size1>=size2)
	{
		if(strncmp(curr,_str2,size2)==0)
		{	
			return curr -_str1;
		}
		curr++;
		size1--;
	}
	return -1;
}

/*----------------------Q3-------------------------*/
static void reverseString(char* str)
{
	int i,size = strlen(str);
	char tmp;
	for(i=0;i<size/2;i++)
	{
		tmp = str[i]; 
		str[i]=str[size-i]; 
		str[size-i]=tmp;
	}

}

errcode itoa(int k ,char* s)
{
	int i=0 ,curr,neg=0;
	if(!s)
	{
		return ERR_NULL_POINTER;
	}
	if(k<0)
	{
		k=k*(-1);
		neg=1;
	}
	while(k>0)
	{
		curr = k%10;
		s[i++] = curr + '0';
		k /= 10;
	}
	if(neg)
	{
		s[i++]='-';
		
	}
	s[i]='\0';
	reverseString(s);
	return SUCCESS;
}


/*----------------------Q4-------------------------*/

/*
	answear ic c
	both functions use pointers incorrectly becuase they both initiate a pointer within the function and return it's address.
	but those pointers die in the end of the function scope thus they return an address of freed memory (trash)

*/

/*----------------------Q5-------------------------*/

/*
	y equals 4 , becuase ptr points to the address of x + 4 , and y equals to the substraction addresses  ptr-x meaning (x+4)-x= 4

*/

/*----------------------Q6-------------------------*/

static int IsValid(const char* str)
{
	while(*str!='\0')
	{
		if(*str<'a' || *str>'o')
		{
			return 0;
		}
		str++;
	}
	return 1;
}

static unsigned char compress(char _a ,char _b)
{
	unsigned char res=0;
	if(_b!= 0)
	{
		_b = _b -'a' +1;
	}
	_a= _a - 'a' + 1;
	res = _a << 4;
	res |= _b;
	return res;
	
}

errcode compressString(char* str)
{
	register int i=0,j=0;
	int size ;
	if(!_str || !IsValid(_str))
	{
		return ERR_ILLEGAL_INPUT;
	}
	size = strlen(_str);
	while(i<size)
	{
		_str[j++] = compress(_str[i],_str[i+1]);
		i+=2;
	}
	_str[j] = '\0';
	return SUCCESS;
}

/*----------------------Q7-------------------------*/

int main(int agrc ,char* argv)
{
	if(arc!=1)
	{
		return -1;
	}
	calcSeriesSum(argv[1]);
	return 0;
}

int calcSeriesSum(size_t n)
{
	double sum=0;
	size_t len=1,lenfac=1;
	FILE* fp;
	if(n==0)
	{
		return -1;
	}
	fp=fopen('w',"keep_result.txt");
	if(!fp)
	{
		return -1;
	}
	if(!feof(fp))
	{
		fscanf(fp,"%f%lu%lu",&sum,&len,&lenfac);
		while(!feof(fp) || len<=n)
		{
			fscanf(p,"%f%lu%lu",&sum,&len,&lenfac);
		}
	}
	while(len <= n)
	{
		lenfac *=len;
		sum += (len / lenfac) ;
		fprintf(fp,"%f %lu %lu",sum,len,lenfac);
		len++;

	}
	fclose(fp);
	return sum;
}



