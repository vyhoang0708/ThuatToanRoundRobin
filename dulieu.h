#include<conio.h>
#include<math.h>
#include <sstream>
#include <string>
using namespace std;

bool isLetter(char c){
	
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z' ) || (c == ' '))
		return 1;
		
	return 0;	 
}


bool isNum(char c){
	
	if((c >= '0' && c <= '9') || (c == '.'))
		return 1;
		
	return 0;	 
}

unsigned long long ChangeCharToNum (char str[]){
	
	unsigned long long n = 0;
	for(int i = 0; i<strlen(str); i++){
		
		n = n * 10;
		n += (str[i]-48);
	}
	return n;
}
char* toChars(unsigned long long num){
	
	char* a = new char[100];
	if (num == 0)
	{
		a[0] = '0';
		a[1] = '\0';
	}
	else
	{
		int l = floor(log10(num)+1);
		a[l--] = '\0';
		while(num>0)
		{
			a[l--] = num%10+48; //to char
			num/=10;
		}
	}
	return a;
}

void AddChuoi(char c,char str[]){
	
	strncat(str, &c , 1);
}

int checkNhapLieu(char c, char s[]){
	
	if(strlen(s) == 0 && c == ' ') // Khoa Phim Cach Nhap Vao Chuoi Rong
		return 0;
else if(strlen(s) != 0 && s[strlen(s)-1] == ' ' && c == ' ') //Khoa Nhap 2 Phim Cach Lien Tiep
			return 0;	
else if((strlen(s) != 0 && s[strlen(s)-1] == ' ' && c != ' ') || (strlen(s) == 0 && c != ' '))//  Viet Hoa Tu Dau Tien Hoac Sau Dau Cach
			return -1;
			
	return 1;	 
}

bool choPhepNhap(char s[], int n){
	if(strlen(s)<n)
		return 1;
	return 0;	
}
char* floatToChars(float so){
	stringstream ss;
	ss << so;
	string tr;
	tr = ss.str();
	char* s = new char [tr.length()+1];;
	strcpy(s, tr.c_str());
	return s;
}

void Nhap(int x,int y,int kieuChuanHoa, char c, char *s, int n){
	
	if(kieuChuanHoa == 0)     //NHAP SO
	{
		if(isNum(c) && choPhepNhap(s,n)){
				AddChuoi(c,s);
		}
	}
	else
	if(kieuChuanHoa== 2)   // Nhap Chu So Thong Thuong
	{
		if((isNum(c) || isLetter(c)) && choPhepNhap(s,n))
		{
			
			if(checkNhapLieu(c,s) == 1){
				AddChuoi(c,s);
			}
			else
				if(checkNhapLieu(c,s)==-1){
					c = toupper(c);
					AddChuoi(c,s);
				}
		}
	}
 	outtextxy(x,y,s);	
}
