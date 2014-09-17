#include<iostream>
#include<string>
#include<windows.h>
#include<tlhelp32.h>
using namespace std;
#pragma comment(lib,"User32.lib")



int main(){
	
	system("color a");
	system("title 进程工具---中国深点科技");
	MessageBox(NULL,TEXT("欢迎使用:\n[进程结束工具]\n[www.libiao.dx.am]"),TEXT("中国深点科技"),MB_OK+MB_ICONINFORMATION);
start:	system("tasklist");
HANDLE kuaizhao;
kuaizhao=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
bool result;
string name;
cout<<"\n输入需要结束的进程名称:";
cin>>name;
char select;
int killnum=0;
PROCESSENTRY32 info;
result=Process32First(kuaizhao,&info);
while(result){

	if(info.szExeFile==name){
		cout<<'\a'<<"\n\n  您是否决定结束 ["<<info.szExeFile<<"] 进程(Y/N):";
		cin>>select;
		if((select=='y')||(select=='Y')){
		    HANDLE kill;
			kill=OpenProcess(PROCESS_TERMINATE,FALSE,info.th32ProcessID );
			if(kill){
				if(TerminateProcess(kill,0)){
					cout<<"\n   结束进程成功!\n";
					killnum++;
				} 
				else{
				   cout<<"\n    结束进程失败!\n";
				}
			
			}
		}
	
	}
	cout<<"进程名--> [ "<<info.szExeFile<<" ]\n";
	result=Process32Next(kuaizhao,&info);


}
if(killnum==0){
  cout<<"\n\n没有你输入的进程，请注意大小写和名称的完整性！";
}
CloseHandle(kuaizhao);
cout<<"\n\n";
system("pause");
system("cls");
goto start;
return 0;
}






