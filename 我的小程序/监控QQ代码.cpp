#include<iostream>
#include<string>
#include<windows.h>
#include<tlhelp32.h>
using namespace std;
#pragma comment(lib,"User32.lib")



int main()
{	
HWND winhide1;
SetConsoleTitle("cmdhide");
start:
winhide1=FindWindow(NULL,"QQ2013");
if(winhide1==0)
  {
     Sleep(3000);
     goto start;
  }

if(winhide1==0)
    {
        cout<<"句柄获取失败！\n";
     }
else
     {
       cout<<"程序已经启动！\n";
	 goto kill;
     }  

kill:
        DWORD pidnum;
         HANDLE kuaizhao=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
         PROCESSENTRY32  info;
         info.dwSize=sizeof(PROCESSENTRY32);
		 bool result=1;
		 result=Process32First(kuaizhao,&info);
		 while(result)
		 {
             string name;
			 name="QQ.exe";
			if(info.szExeFile==name)
			{
			   pidnum=info.th32ProcessID;
			   HANDLE Hkillpro=OpenProcess(PROCESS_TERMINATE,FALSE,pidnum);
			   if(Hkillpro)
			   {
			        if(TerminateProcess(Hkillpro,0))
					{
					  cout<<"保护完成!\n";
					  goto start;
					}
					else
					{
					  cout<<"保护失败\n";
					}
			   }


			}
			 result=Process32Next(kuaizhao,&info);
		 }

system("pause");
return 0;
}






