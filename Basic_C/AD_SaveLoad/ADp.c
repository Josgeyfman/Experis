#include"ADp.h"

struct Meeting 
{
	float startTime;
	float endTime;
	int roomNum;

};

struct AD_T 
{
	meetp * diary;
	size_t blockSize;
	size_t elementNum;
	size_t size; 
}; 

ERRCODE SaveDiary(ad_p _adPtr)
{
	FILE* fp;
	int i;       
	fp = fopen("diary.txt", "w");        	
	if(fp == NULL)  
	{                    
		printf("Error in file opening\n");
		return ERR_FILE_OPEN;
	}
	
	fprintf(fp,"%-20lu%-20lu%lu\n",_adPtr->blockSize,_adPtr->elementNum,_adPtr->size);
	for(i=0;i<_adPtr->elementNum;i++)
	{
		fprintf(fp,"%-20f%-20f%d\n",_adPtr->diary[i]->startTime,_adPtr->diary[i]->endTime,_adPtr->diary[i]->roomNum);
	}
	
	fclose(fp);
	return ERR_SUCCESS;

}

ERRCODE LoadDiary(ad_p* _adPtr)
{
	FILE* fp;
	size_t blockSize,elementNum,size;
	float startTime,endTime;
	int i ,roomNum;   
	ERRCODE result;
	meetp mp;
	
	fp = fopen("diary.txt", "r");        	
	if(fp == NULL)  
	{                    
		return ERR_FILE_OPEN;
	}
	if((*_adPtr) != NULL)  
	{                    
		return ERR_ALREADY_EXISTS;
	}
	
	fscanf(fp,"%lu%lu%lu",&blockSize,&elementNum,&size);
	(*_adPtr) = CreateAD(size,blockSize);
	for(i=0;i<elementNum;i++)
	{
		fscanf(fp,"%f%f%d",&startTime,&endTime,&roomNum);
		result = CreateMeeting(&mp,startTime,endTime,roomNum);
		if(result==ERR_SUCCESS)
		{
			result = InsertMeet((*_adPtr),&mp);
			if(result!=ERR_SUCCESS)
			{
				return result;
			}
		}
	}
	
	fclose(fp);
	return ERR_SUCCESS;

}

ERRCODE SetAD(ad_p _adPtr, meetp* _diaryPtr, size_t _initialSize , size_t _blockSize , size_t _elementNum)
{
	if(_adPtr !=NULL)
	{
		_adPtr->diary      = _diaryPtr;
		_adPtr->blockSize  = _blockSize;
		_adPtr->size	   = _initialSize; 
		_adPtr->elementNum = _elementNum; 
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
	
}


ad_p CreateAD(size_t _initialSize,size_t _blockSize)
{
	ad_p adPtr = NULL;
	meetp* diaryPtr =NULL;
	ERRCODE result;
	if(_initialSize > 0 && _blockSize>0 )
	{
		adPtr = (ad_p)malloc(sizeof(ad_t));
		if(adPtr != NULL)
		{
			diaryPtr=(meetp*)malloc(_initialSize*sizeof(meetp));
			if(diaryPtr!=NULL)
			{
				result = SetAD(adPtr,diaryPtr,_initialSize,_blockSize,0);
				if(result != ERR_SUCCESS)
				{
					free(diaryPtr);
					diaryPtr=NULL;
					free(adPtr);
					adPtr=NULL;
				}
			}
			else
			{
				free(adPtr);
				adPtr=NULL;
			}
		}
	}
	return adPtr;
}	


ERRCODE SetMeeting(meetp* _meetPtr,float _startTime,float _endTime,int _roomNum)
{
	if((*_meetPtr)!=NULL)
	{
		(**_meetPtr).startTime	= _startTime;
		(**_meetPtr).endTime	= _endTime;
		(**_meetPtr).roomNum	= _roomNum;
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
}

int CheckInput(float _startTime ,float _endTime ,int _room)
{
	int hour = (int)(_startTime);
	float minutes = _startTime - hour;
	if( hour >= MIN_HOUR && hour < MAX_HOUR &&  minutes>=MIN_MINUTE && minutes<MAX_MINUTE)
	{
		
		hour = (int)(_endTime);
		minutes = _endTime - hour;
		if( hour >= MIN_HOUR && hour < MAX_HOUR &&  minutes>=MIN_MINUTE && minutes<MAX_MINUTE)
		{
			if( _room > 0 )
			{
				return 1;
			}
		}
	}
	return 0;
}

ERRCODE CreateMeeting(meetp* _newMeet,float _startTime,float _endTime ,int _roomNum)
{
	
	_startTime  =	((int)(_startTime*100+.5)/100.0);
	_endTime    =	((int)(_endTime*100+.5)/100.0);	
	if(_endTime >_startTime && CheckInput(_startTime,_endTime,_roomNum))
	{
		(*_newMeet) = (meetp)malloc(sizeof(meet));
		if((*_newMeet) != NULL)
		{
			SetMeeting(_newMeet,_startTime,_endTime,_roomNum);
		}
		else
		{
			return ERR_MEM_ALLOC;
		}
	}
	else
	{
		return ERR_ILLEGAL_INPUT;
	}
	return ERR_SUCCESS;
}

void DestroyAD(ad_p _adPtr)
{
	int i;
	if(_adPtr!=NULL)
	{
		if(_adPtr->diary!=NULL)
		{
			for(i=0;i<_adPtr->elementNum;i++)
			{	
				free((_adPtr->diary)[i]);
			}
		}
		free(_adPtr);
	}
}

void PrintMeeting(meetp _meetPtr)
{
	if(_meetPtr!=NULL)
	{
		printf("[start time:%.2f end time:%.2f room num:%d]\n"
				, _meetPtr->startTime,_meetPtr->endTime,_meetPtr->roomNum);
	}
}


int PrintAD(ad_p _adPtr)
{
	int i = -1;
	if(_adPtr!=NULL)
	{
		printf("AD size:%ld blockSize:%ld element num:%ld\n" ,_adPtr->size,_adPtr->blockSize,_adPtr->elementNum);
		for(i=0;i<_adPtr->elementNum;i++)
		{
			printf("Meeting No:%d ",i+1);
			PrintMeeting(_adPtr->diary[i]); 
		}
	}
	return i;
}


ERRCODE ResizeDiary(ad_p _adPtr)
{
	meetp* mp = _adPtr->diary;
	size_t newSize = _adPtr->size+_adPtr->blockSize;
	if(NULL!=mp || newSize>0)
	{
		mp = (meetp*)realloc((_adPtr->diary),newSize*sizeof(meetp));
		if(mp!=NULL)
		{
			_adPtr->size+=_adPtr->blockSize;
			_adPtr->diary = (mp);
			return ERR_SUCCESS;
		}
		return ERR_MEM_ALLOC;
	}
	return ERR_ILLEGAL_INPUT;	
}

ERRCODE CheckOverlap(ad_p _adPtr,float _startTime,float _endTime)
{
	int i;
	if(_adPtr != NULL && _startTime < _endTime)
	{
		for(i=0;i<_adPtr->elementNum;i++)
		{
			if((_adPtr->diary)[i]->startTime <=_startTime && (_adPtr->diary)[i]->endTime > _startTime) 
			{
				return ERR_OVERLAP;
			}
			if((_adPtr->diary)[i]->startTime < _endTime && (_adPtr->diary)[i]->endTime >= _endTime) 
			{
				return ERR_OVERLAP;
			}
			if((_adPtr->diary)[i]->startTime >= _startTime && (_adPtr->diary)[i]->endTime <= _endTime) 
			{
				return ERR_OVERLAP;
			}		
		}
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT; 
}

void SwapMeeting(meetp* _meet1,meetp* _meet2)
{
	meetp temp;

	temp      = (*_meet1);
	(*_meet1) = (*_meet2);
	(*_meet2) =  temp;

}

void BubbleSortDiary(meetp* _diary,size_t _size)
{
	int i,j,swapped;
	for(i=0;i<_size-1;i++)
	{
		swapped=0;
		for(j = 0 ;j < _size-i-1 ; j++)
		{
			if((_diary[j])->startTime > (_diary[j+1])->startTime)
			{
				SwapMeeting(&_diary[j],&_diary[j+1]);
				swapped=1;
			}
		}
		if(!swapped){
			break;
		}
	}
}

ERRCODE InsertMeet(ad_p _adPtr,meetp* _newMeet)
{
	ERRCODE result = ERR_ILLEGAL_INPUT;
	if(_adPtr!=NULL && (*_newMeet)!=NULL )
	{
		result = CheckOverlap(_adPtr,(*_newMeet)->startTime,(*_newMeet)->endTime);
		if(result==ERR_SUCCESS)
		{
			if(_adPtr->elementNum == _adPtr->size)
			{
				result = ResizeDiary(_adPtr);
				if(ERR_SUCCESS!=result)
				{

					return result;
				}
			}
			(_adPtr->diary)[(_adPtr->elementNum)++] = (*_newMeet);
			BubbleSortDiary(_adPtr->diary,_adPtr->elementNum);
			_newMeet=NULL;
			
		}
	}
	return result;	
}

int FindMeet(ad_p _adPtr,float _startTime)
{
	int i;
	if(_adPtr!=NULL)
	{
		if(_adPtr->elementNum>0)
		{		
			for(i=0;i<_adPtr->elementNum;i++)
			{
				if((_adPtr->diary)[i]->startTime == _startTime) 
				{
					return i;
				}
			}
			return -3;
		}
		return -2;
	}
	return -1;
}

ERRCODE RemoveMeet(ad_p _adPtr,float _startTime)
{
	int i;
	i = FindMeet(_adPtr,_startTime);
	if(i>=0)
	{
		(_adPtr->diary)[i]->startTime = MAX_HOUR;
		if(_adPtr->elementNum>1)
		{
			BubbleSortDiary(_adPtr->diary,_adPtr->elementNum);
		}
		free((_adPtr->diary)[(_adPtr->elementNum)--]);
		return ERR_SUCCESS;
	}
	return i;
	
}

void PrintERRCODE(ERRCODE _err)
{
	switch(_err)
	{
		case ERR_SUCCESS: 		printf("ERR_SUCCESS\n"); 	break;
		case ERR_ILLEGAL_INPUT: 	printf("ERR_ILLEGAL_INPUT\n");  break;
		case ERR_UNDERFLOW: 		printf("ERR_UNDERFLOW\n"); 	break;
		case ERR_NOT_FOUND: 		printf("ERR_NOT_FOUND\n"); 	break;
		case ERR_MEM_ALLOC: 		printf("ERR_MEM_ALLOC\n"); 	break;
		case ERR_OVERLAP: 		printf("ERR_OVERLAP\n"); 	break;
		case ERR_FILE_OPEN:		printf("ERR_FILE_OPEN\n"); 	break;
		case ERR_ALREADY_EXISTS:	printf("ERR_ALREADY_EXISTS\n"); break;
	}
}


