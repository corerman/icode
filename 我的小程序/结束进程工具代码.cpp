#include<iostream>
#include<string>
#include<windows.h>
#include<tlhelp32.h>
using namespace std;
#pragma comment(lib,"User32.lib")



int main(){
	
	system("color a");
	system("title ���̹���---�й����Ƽ�");
	MessageBox(NULL,TEXT("��ӭʹ��:\n[���̽�������]\n[www.libiao.dx.am]"),TEXT("�й����Ƽ�"),MB_OK+MB_ICONINFORMATION);
start:	system("tasklist");
HANDLE kuaizhao;
kuaizhao=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
bool result;
string name;
cout<<"\n������Ҫ�����Ľ�������:";
cin>>name;
char select;
int killnum=0;
PROCESSENTRY32 info;
result=Process32First(kuaizhao,&info);
while(result){

	if(info.szExeFile==name){
		cout<<'\a'<<"\n\n  ���Ƿ�������� ["<<info.szExeFile<<"] ����(Y/N):";
		cin>>select;
		if((select=='y')||(select=='Y')){
		    HANDLE kill;
			kill=OpenProcess(PROCESS_TERMINATE,FALSE,info.th32ProcessID );
			if(kill){
				if(TerminateProcess(kill,0)){
					cout<<"\n   �������̳ɹ�!\n";
					killnum++;
				} 
				else{
				   cout<<"\n    ��������ʧ��!\n";
				}
			
			}
		}
	
	}
	cout<<"������--> [ "<<info.szExeFile<<" ]\n";
	result=Process32Next(kuaizhao,&info);


}
if(killnum==0){
  cout<<"\n\nû��������Ľ��̣���ע���Сд�����Ƶ������ԣ�";
}
CloseHandle(kuaizhao);
cout<<"\n\n";
system("pause");
system("cls");
goto start;
return 0;
}






