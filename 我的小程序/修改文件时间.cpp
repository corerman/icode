#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include <time.h> 
#pragma comment(lib,"User32.lib")
using namespace std;

int main(){
 system("color a");
 system("title �ļ�ʱ����Ϣ�޸�---�й����Ƽ�");
 char way[50];
start: cout<<"\n   ��������·��:";
 cin>>way;
   HANDLE hfile;
   DWORD panduan;
   panduan=GetFileAttributes(way);
   if(panduan!=32){
   cout<<"�ļ�Ŀ¼������!\n";
   }
   else{
  hfile=CreateFile(way,GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  SYSTEMTIME systime;
  int year;
  int month;
  int day;
  cout<<"��������:";
  cin>>year;
  cout<<"�����·���:";
  cin>>month;
  cout<<"����������:";
 cin>>day;
  GetLocalTime(&systime);
  systime.wDay=day;
  systime.wYear=year;
  systime.wMonth=month;
  FILETIME time2;
  if(SystemTimeToFileTime(&systime,&time2)){
     cout<<"\nʱ��ת���ɹ���\n";
                if(SetFileTime(hfile,&time2,&time2,&time2)){
                                   cout<<"\n�޸�ʱ��ɹ�!\n";
                                 }
                else{
                       cout<<"�޸�ʱ��ʧ��!\n";
                    }
                }
  else{
  cout<<"ʱ��ת��ʧ�ܣ�\n";
  }

  cout<<"ʱ��:"<<systime.wYear<<"��"<<systime.wMonth<<"��"<<systime.wDay<<"��\n";
}
system("pause");
system("cls");
goto start;
return 0;
}