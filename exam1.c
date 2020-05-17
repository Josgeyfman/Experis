void bubbleSortPatient(struct _patient[],int _len,int _sortByMoney)
{
	int i,j,swapped=0;
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-i-1;j++)
		{
			if(_sortByMoney)
			{
				if(_patient[j].money>_patient[j+1].money)
				{
					SwapPatient(_patient[j],_patient[j+1]);
					swapped=1;
				}
			}
			else if(_patient[j]->ID>_patient[j+1]->ID)
			{
					SwapPatient(_patient[j],_patient[j+1]);
					swapped=1;
			}
			
			if(!swapped)
			{
				break;
			}
		
		}
		swapped = 0;
	
	}

}

void SwapPatient(Patient* _patient1 ,Patient* _patient2)
{
	Patient p1 = (*_patient1);
	(*_patient1) = (*_patient2);
	(*_patient2) = p1;

}