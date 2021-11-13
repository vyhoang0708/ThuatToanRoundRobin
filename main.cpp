
#include <winbgim.h> 
#include <iostream> 
#include <fstream>
#include "dulieu.h"
#include "xuly.h"
#include <sstream>
#include <string>

void setID(int id,int x1,int y1, int x2,int y2,unsigned short int ** mapID){
	
	for(int i=y1 ; i<=y2 ; i++)
		for(int j=x1; j <= x2; j++)
			mapID[i][j] = id ;
		
}

void resetMapID(unsigned short int ** mapID){
	
		for(int i = 0; i<= 650; i++)
		{
			for(int j = 0; j <=1200; j++)
			    mapID[i][j] = 0;
		}

}
void taoButton(int id, int x1, int y1, int x2, int y2, unsigned short int **mapID, int mauVien, int mauText , int mauBG , char *text){
	
		setcolor(mauVien);
		setfillstyle(1, mauBG);
		bar(x1, y1, x2, y2);
		rectangle(x1, y1, x2, y2);
		
		setcolor(mauText);
		setbkcolor(mauBG);
		outtextxy(x1+(x2-x1-textwidth(text))/2,y1+(y2-y1-textheight(text))/2, text);
		
		setID(id,x1,y1,x2,y2,mapID);
	
}
void taoEditText(int id, int x1, int y1, int x2, int y2, unsigned short int **mapID, int mauVien, int mauBG){
	
		setcolor(mauVien);
		setfillstyle(1, mauBG);
		bar(x1, y1, x2, y2);
		rectangle(x1, y1, x2, y2);
		
		setID(id,x1,y1,x2,y2,mapID);
	
}
void taoLable(int x1, int y1, int x2, int y2, int mauVien,int mauText, int mauBG, char* text){
	
		setcolor(mauVien);
		setfillstyle(1, mauBG);
		bar(x1, y1, x2, y2);
		rectangle(x1, y1, x2, y2);
		
		setcolor(mauText);
		setbkcolor(mauBG);
		outtextxy(x1+(x2-x1-textwidth(text))/2,y1+(y2-y1-textheight(text))/2, text);	
}
void Input(int x,int y,int kieuChuanHoa, char s[], int n, int &id,unsigned short int **mapID,bool &kt){
	kt=0;
	char c;
	int idtmp=id;
	int h,k;
	setbkcolor(15);
	setcolor(0);
	while(true){
			if(ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN, h, k);
				idtmp = mapID[k][h];
				clearmouseclick(WM_LBUTTONDOWN);
	      	  }
	      	  
	      	if(id != idtmp) {
			 	 kt=1;
			  	id=idtmp;
			  	if(s[strlen(s)-1]==' ')
			    	s[strlen(s)-1]='\0';
			  	return ;
			  }
	      	
		    if (kbhit()){
				c=getch();
				if(c!= 13){
						if(c==8 && strlen(s) != 0)  {    //Phim BackSpace
							outtextxy(x+textwidth(s),y," ");
							s[strlen(s)-1] = '\0';	
						  }
					   else	Nhap(x,y,kieuChuanHoa,c,s,n);
					}
				else {
						if(s[strlen(s)-1]==' ')
		    				s[strlen(s)-1]='\0';
						return ;
					}
				}
			else { 
					outtextxy(x+textwidth(s),y,"|");
					outtextxy(x+textwidth(s),y," ");	
				}
	
	}
}
void bang(int n, unsigned short int **mapID){
	for(int i = 0; i< n; i++)
	{
	    taoEditText(10*(i+1) + 0,550,100+(150/n)*i,700,100+(150/n)*(i+1),mapID,0,15);
		taoEditText(10*(i+1) + 1,700,100+(150/n)*i,900,100+(150/n)*(i+1),mapID,0,15);
		taoEditText(10*(i+1) + 2,900,100+(150/n)*i,1110,100+(150/n)*(i+1),mapID,0,15);
	}
	// id bang 10->12, 20->22, ... n0->n2
}
void bangxuat(listRL &ds,list &dsRL, int n, int quantum, int soluong)
{
	taoLable(400,260,800,290,0,0,11,"Ket qua dieu phoi tien trinh");
	for(int i=0; i<n; i++)
	{
		if(i == n-1)
		{
			taoLable(150+(900/n*i),300,150+((900/n) * (i+1)),335,0,0,11,"");
		    taoLable(150+(900/n*i),335,150+((900/n) * (i+1)),385,0,0,15,floatToChars(ds.dataRL[n-2]->TimeOut));
		}
		else
		{
			taoLable(150+(900/n*i),300,150+((900/n) * (i+1)),335,0,0,11,ds.dataRL[i]->Name);
		    taoLable(150+(900/n*i),335,150+((900/n) * (i+1)),385,0,0,15,floatToChars(ds.dataRL[i]->TimeRL));
		}	
	}
	float sum = 0;
	int count = 0;
	taoLable(200,410,500,440,0,0,11,"Thoi gian cho");
	for(int i=0; i<ds.soluong; i++){
		if(ds.dataRL[i]->TimeWait != 0){
			taoLable(200,450+(150/soluong)*count,350,450+(150/soluong)*(count+1),0,0,11,ds.dataRL[i]->Name);
		    taoLable(350,450+(150/soluong)*count,500,450+(150/soluong)*(count+1),0,0,15,floatToChars(ds.dataRL[i]->TimeWait));	
			sum += 	ds.dataRL[i]->TimeWait;
			count++;
		}
		
	}
	taoLable(600,410,900,440,0,0,11,"Thoi gian trung binh");
	sum = sum/count;
	taoLable(600,450,900,480,0,0,15,floatToChars(sum));
}
void nhapdulieu(list &listRL, int soluong, unsigned short int **mapID)
{
	bool kt=0;
	int x,y;
	int id=1;
	char chartemp;
	char sa[50]="";
	char name[10] = "";
	float timeRL=0, timeCPU=0;
	RoundRobin *RR;
    bool T = true;
	while(T){
		
		delay(100);
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			id = mapID[y][x];
			clearmouseclick(WM_LBUTTONDOWN);
		}
		if (kbhit()){    // Bat Phim Khi Chua CLick Vao EdiitText
				    chartemp=getch();
				    break;
				}
		
        for(int i=0; i<soluong; i++){
          
N:        
			if(id == (10*(i+1) + 0))
            {
            	name[0]='\0';
            	 id = 10*(i+1)+0;
    			 Input(555,100+(150/soluong)*i +(150/(soluong*3)),2,name,10,id,mapID,kt);
    			 if(kt==1) goto N;
			     break;
			}
			if(id == (10*(i+1) + 1))
			{
				id = 10*(i+1)+1;
				sa[0]='\0';
    			 Input(705,100+(150/soluong)*i +(150/(soluong*3)),0,sa,10,id,mapID,kt);
    			 timeRL = atof(sa);
    			 if(kt==1) goto N;
			     break;
			}
			if(id == (10*(i+1) + 2))
			{
				id = 10*(i+1)+2;
				sa[0]='\0';
    			 Input(905,100+(150/soluong)*i +(150/(soluong*3)),0,sa,10,id,mapID,kt);
    			 timeCPU = atof(sa);
    			 if(kt==1) goto N;
			     break;
			}
			if(timeCPU != 0)
			{
				RR = newRR(name,timeRL,timeCPU);
				addvaoList(listRL, RR);
			}
			
   	    } 
	   	if(id == 0)
	    	return ;
		
    	delay(100);
	}
}
int main(int argc, char *argv[])
{
	
	unsigned short int **mapID = new unsigned short int *[650];
	for(int i=0;i<= 650;i++)
	 	mapID[i]= new unsigned short int[1200];
	 	
	resetMapID(mapID);
	
	
	initwindow(1200, 650);
	setwindowtitle("Thuat Toan Round Robin 1.0");			// init window graphics	
	char s[50]="";
	bool kt=0;
	int x,y;
	int id=0;
	int quantum=0, soluong=0 ; // quantum + so luong tien trinh
	char chartemp;
	list dsRL;
	listRL ds;
	
	setbkcolor(15);					// set background
   	cleardevice();
	setcolor(0);
	settextstyle(0,0,2);
	taoLable(0,0,1200,50,15,0,11,"Thuat toan phan phoi xoay vong Round Robin");
	settextstyle(8,0,1);
	taoLable(30,70,300,100,0,0,11,"So luong tien trinh");
	taoLable(30,110,300,140,0,0,11,"Quantum");
	taoLable(550,70,700,100,0,0,11,"Ten t.trinh");
    taoLable(700,70,900,100,0,0,11,"Thoi gian vao RL");
    taoLable(900,70,1110,100,0,0,11,"Thoi gian xu ly");
	taoEditText(1,305,70,450,100,mapID,0,15);// nhap so luong tien trinh
	taoEditText(2,305,110,450,140,mapID,0,15); // nhap quantum
	taoButton(3,150,150,350,180,mapID,0,0,11,"Nhap du lieu");
	taoButton(4,150,190,350,220,mapID,0,0,11,"Thuc Hien");
	while(true){
		
		id=0;
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			id = mapID[y][x];
			clearmouseclick(WM_LBUTTONDOWN);
		}
		
RR:		switch(id){
			case 1:
				id = 1;
				Input(310,75,0,s,10,id,mapID,kt);
				soluong = ChangeCharToNum(s);
				s[0]='\0';
				if(kt==1) goto RR;
				break;
			case 2:
				id = 2;
				Input(310,115,0,s,10,id,mapID,kt);
				quantum = ChangeCharToNum(s);
				if(kt==1) goto RR;
				break;
			case 3:
				id = 3;
				s[0]='\0';
				bang(soluong,mapID);
				nhapdulieu(dsRL,soluong,mapID);
				xuat(dsRL);
				break;
			case 4:
				Sort(dsRL,soluong);
				thuattoan(ds,dsRL,soluong,quantum);
				bangxuat(ds,dsRL,ds.soluong+1,quantum, soluong);
			    taoButton(5,850,570,1050,600,mapID,0,0,11,"Reset");
				break;
			case 5:
				deleteDs(ds);
				ds.soluong = 0;
				taoEditText(1,305,70,450,100,mapID,0,15);// nhap so luong tien trinh
            	taoEditText(2,305,110,450,140,mapID,0,15); // nhap quantum
            	quantum=0;
				soluong=0 ;
				setfillstyle(1,15);
				bar(550,101,1111,251);
				bar(0,250,1200,650);
			    break;
			default:
	            if (kbhit()){    // Bat Phim Khi Chua CLick Vao EdiitText
				    chartemp=getch();
				    break;
				}
		}
		delay(100);
	}
	while(!kbhit()) delay(1);		// pause screen	
	return 0;
}
