#include<iostream>
#include<windows.h>
using namespace std;

int main(){
	
	int num=0;//�����ƶ���;
	DWORD driver;//�����������б����;
	DWORD num2=0;//�������ƺ󴢴����;
	char a='A'; //�����ʼ������;
	int  i=0;//�������ӱ���;
	char drivelist[40];//�����������б�;
    driver=GetLogicalDrives();
	if(driver){
	  while(num<=32){
	         num2=driver;
			 num2=num2>>num;//�����ǴӵͶ�����λ��ʼ����;
			 if((!(num2&1))&&(num>=2)){
			     cout<<"\n�������б����!\n\n";
				 break;
			 }
			 else
				 if(num2&1){
			     drivelist[i]=a+i;
			 }
			 i++;
			 num++;
          
	  }

	}
	else{
	  cout<<"�������б��ȡʧ��!";
	}
int listnum=0;
listnum=sizeof(drivelist)/sizeof(char);
for(int a=0;a<listnum;a++){
	if((drivelist[a]>='A')&&(drivelist[a]<='Z')){
	cout<<"����������:  ["<<drivelist[a]<<"]\n";
	}
}
cout<<"\n\n";
system("pause");
return 0;

}