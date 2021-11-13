#define MAX 200

struct RoundRobin{
	char Name[10];
	float  TimeRL;
	float  TimeCPU;
	float  TimeWait = 0, TimeOut = 0, timeXl = 0, TimeVaoRL = 0;
};

struct list{
	RoundRobin *data[100];
	int soluong = 0;
	list(){};
};

struct listRL{
	RoundRobin *dataRL[MAX];
	int soluong = 0;
	listRL(){};
};

RoundRobin *newRR(char *Name, float timeRL, float timeCPU){
	RoundRobin *temp = new RoundRobin;
	strcpy(temp->Name,Name) ;
	temp->TimeRL= timeRL;
	temp->TimeVaoRL= timeRL;
    temp->TimeCPU = timeCPU;
    return temp;
}	
void addvaoList(list &listRR,RoundRobin *newRR ){
	listRR.data[listRR.soluong] = new RoundRobin;
	listRR.data[listRR.soluong] = newRR;
	listRR.soluong ++;
}

void xuat(list &listRR){
	for(int i=0; i< listRR.soluong;i++){
		cout<<listRR.data[i]->Name<<"     "<<listRR.data[i]->TimeRL<<"     "<<listRR.data[i]->TimeCPU<<"     " << listRR.data[i]->TimeWait;
		cout<<endl;
	}
}
void xuatRL(listRL &listRR){
	cout<< "ten" << "    " << "RL" <<"    " << "cpu" << "    " << "xl" << "    " << "out" << endl;
	for(int i=0; i< listRR.soluong;i++){
		cout<<listRR.dataRL[i]->Name<<"     "<<listRR.dataRL[i]->TimeRL<<"     "<<listRR.dataRL[i]->TimeCPU<<"     " << listRR.dataRL[i]->timeXl <<"     " << listRR.dataRL[i]->TimeOut << "     "<< listRR.dataRL[i]->TimeWait;
		cout<<endl;
	}
}
void swap(RoundRobin &R1, RoundRobin &R2) {
    RoundRobin temp;
    temp = R1;
    R1 = R2;
    R2 = temp;
}
void Sort(list &list , int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (list.data[j]->TimeRL > list.data[j+1]->TimeRL)
                swap(list.data[j], list.data[j+1]); 
}
void add_cuoids(list &list, int vitri){
    list.soluong++;
    list.data[list.soluong-1] = new RoundRobin;
    *list.data[list.soluong -1] = *list.data[vitri];
    	     
}
void xoa(list &list, int vitri)
{
	for(int i=vitri; i< list.soluong -1; i++ )
		*list.data[i]= *list.data[i+1];
		
	     list.soluong--;
}
void add(list &dsRL, listRL &ds, int vitri)
{
	ds.dataRL[ds.soluong] = new RoundRobin;
	*ds.dataRL[ds.soluong] = *dsRL.data[vitri];
	ds.soluong ++;
}

void thuattoan(listRL &ds,list &dsRL, int soluong, int quantum)
{
	int count = 0;
    float i = 0;
	i = dsRL.data[0]->TimeRL;
	while( dsRL.soluong > 0 )
	{
		
		if(count < quantum && dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl >0)
		{
			if(dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl < 1){
				i = i - (1.0 - (dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl));
				dsRL.data[0]->timeXl += dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl;
				cout << i << endl;
			}
			else
			    dsRL.data[0]->timeXl++; 
		}
		        
		else if(count == quantum && dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl >0)
		{
			add_cuoids(dsRL, 0);
			add(dsRL,ds, 0);
			xoa(dsRL,0);
			count = 0;
			if(dsRL.data[0]->TimeRL > i && dsRL.data[0]->timeXl == 0 )
			{
				swap(ds.dataRL[0],ds.dataRL[1]);
			}
			dsRL.data[0]->TimeRL = i;
			dsRL.data[0]->timeXl++;
		}
		else if( dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl == 0 || (count == quantum && dsRL.data[0]->TimeCPU - dsRL.data[0]->timeXl == 0))
		{
			dsRL.data[0]->TimeOut = i;
			add(dsRL,ds, 0);
			xoa(dsRL,0);
			if(dsRL.soluong == 0){
				break;
			}
			count = 0;
			dsRL.data[0]->TimeRL = i;
			dsRL.data[0]->timeXl++;
		}
		count++;
		i = i+1;
	}
	
	xuat(dsRL);
	for(int i = 0 ; i< ds.soluong; i++)
	{
		
		if(ds.dataRL[i]->TimeOut > 0 )
		{
			ds.dataRL[i]->TimeWait = ds.dataRL[i]->TimeOut - ds.dataRL[i]->TimeCPU - ds.dataRL[i]->TimeVaoRL;
		}
	} 
	
}
void deleteDs(listRL &dsRL){
	for(int i = 0; i< dsRL.soluong; i++)
	{
		if(dsRL.dataRL[i] == NULL)
		   return;
		delete dsRL.dataRL[i];
	}
}
