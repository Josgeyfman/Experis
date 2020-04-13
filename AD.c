#include"AD.h"

ERRCODE SetAD(ad_p _adPtr,meetp _meetPtr,size_t _initialSize,size_t _blockSize,size_t _elementNum)
{
	if(_adPtr!=NULL)
	{
		_adPtr->diary	   = _meetPtr;
		_adPtr->blockSize  = _blockSize;
		_adPtr->size	   = _initialSize; 
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
	
}

ad_p CreateAD(size_t _initialSize,size_t _blockSize)
{
	ad_p adPtr = NULL;
	meetp meetPtr =NULL;
	ERRCODE result;
	if(_initialSize > 0 && _blockSize>0 )
	{
		adPtr = (ad_p)malloc(sizeof(ad_t));
		if(adPtr != NULL)
		{
			meetPtr=(meetp)malloc(_initialSize*sizeof(meet));
			if(meetPtr!=NULL)
			{
				result = SetAD(adPtr,meetPtr,_initialSize,_blockSize,0);
				if(result != ERR_SUCCESS)
				{
					free(meetPtr);
					meetPtr=NULL;
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
		(*_meetPtr)->startTime	= _startTime;
		(*_meetPtr)->endTime	= _endTime;
		(*_meetPtr)->roomNum	= _roomNum;
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
}

int CheckInput(float _startTime ,float _endTime ,int _room)
{
	if( _startTime >= MIN_HOUR && _startTime < MAX_HOUR )
	{
		if( _endTime > MIN_HOUR && _endTime < MAX_HOUR )
		{
			if( _room > 0 )
			{
				return 1;
			}
		}
	}
	return 0;
}

int PrintAD(ad_p _adPtr)
{
	int i;
	if(_adPtr!=NULL && _adPtr->diary!=NULL)
	{
		printf("AD size:%ld blockSize:%ld element num:%ld\n" ,_adPtr->size,_adPtr->blockSize,_adPtr->elementNum);
		for(i=0;i<_adPtr->elementNum;i++)
		{
			printf("Meeting No:%d ",i+1);
			PrintMeeting(_adPtr->diary+i); 
		}
	}
}

ERRCODE CreateMeeting(meetp* _newMeet,float _startTime,float _endTime ,int _roomNum)
{
	
	if(*_newMeet!=NULL)
	{
		free(*_newMeet);
		*_newMeet=NULL;
	}	
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
	if(_adPtr!=NULL)
	{
		if(_adPtr->diary!=NULL)
		{
			free(_adPtr->diary);
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


ERRCODE ResizeDiary(ad_p _adPtr)
{
	meetp mp = _adPtr->diary;
	size_t newSize = _adPtr->size+_adPtr->blockSize;
	if(NULL!=mp || newSize>0)
	{
		mp = (meetp)realloc((_adPtr->diary),newSize*sizeof(meet));
		if(mp!=NULL)
		{
			_adPtr->size+=_adPtr->blockSize;
			_adPtr->diary = mp;
			return ERR_SUCCESS;
		}
		return ERR_MEM_ALLOC;
	}
	return ERR_ILLEGAL_INPUT;	
}

ERRCODE CheckOverlap(ad_p _adPtr,float _startTime,float _endTime)
{
	int i;
	if(_adPtr != NULL || _startTime >= _endTime)
	{
		for(i=0;i<_adPtr->elementNum;i++)
		{
			if((_adPtr->diary)[i].startTime <=_startTime && (_adPtr->diary)[i].endTime > _startTime) 
			{
				return ERR_OVERLAP;
			}
			if((_adPtr->diary)[i].startTime < _endTime && (_adPtr->diary)[i].endTime >= _endTime) 
			{
				return ERR_OVERLAP;
			}
			if((_adPtr->diary)[i].startTime >= _startTime && (_adPtr->diary)[i].endTime <= _endTime) 
			{
				return ERR_OVERLAP;
			}		
		}
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT; 
}

void SwapMeeting(meetp _meet1,meetp _meet2)
{
	meet temp;

	temp = (*_meet1);
	(*_meet1) = (*_meet2);
	(*_meet2) =  temp;

}

void BubbleSortDiary(meetp _diary,size_t _size)
{
	int i,j,swapped;
	for(i=0;i<_size-1;i++)
	{
		swapped=0;
		for(j = 0 ;j < _size-i-1 ; j++)
		{
			if((_diary[j]).startTime > (_diary[j+1]).startTime)
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
	if(_adPtr!=NULL && *_newMeet!=NULL )
	{
		result = CheckOverlap(_adPtr,(**_newMeet).startTime,(**_newMeet).endTime);
		if(result==ERR_SUCCESS)
		{
			if(_adPtr->elementNum==_adPtr->size)
			{
				result = ResizeDiary(_adPtr);
				if(ERR_SUCCESS!=result)
				{
					return result;
				}
			}
			(_adPtr->diary)[(_adPtr->elementNum)++] = (**_newMeet);
			BubbleSortDiary(_adPtr->diary,_adPtr->elementNum);
			free(*_newMeet);
			*_newMeet=NULL;
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
				if((_adPtr->diary)[i].startTime == _startTime) 
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
		(_adPtr->diary)[i].startTime = MAX_HOUR;
		if(_adPtr->elementNum>1)
		{
			BubbleSortDiary(_adPtr->diary,_adPtr->elementNum);
		}
		_adPtr->elementNum--;	
		return ERR_SUCCESS;
	}
	return i;
	
}



