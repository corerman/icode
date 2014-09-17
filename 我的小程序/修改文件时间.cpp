#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include <time.h> 
#pragma comment(lib,"User32.lib")
using namespace std;

int main(){
 system("color a");
 system("title 文件时间信息修改---中国深点科技");
 char way[50];
start: cout<<"\n   输入完整路径:";
 cin>>way;
   HANDLE hfile;
   DWORD panduan;
   panduan=GetFileAttributes(way);
   if(panduan!=32){
   cout<<"文件目录不存在!\n";
   }
   else{
  hfile=CreateFile(way,GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
  SYSTEMTIME systime;
  int year;
  int month;
  int day;
  cout<<"输入年数:";
  cin>>year;
  cout<<"输入月份数:";
  cin>>month;
  cout<<"输入日期数:";
 cin>>day;
  GetLocalTime(&systime);
  systime.wDay=day;
  systime.wYear=year;
  systime.wMonth=month;
  FILETIME time2;
  if(SystemTimeToFileTime(&systime,&time2)){
     cout<<"\n时间转换成功！\n";
                if(SetFileTime(hfile,&time2,&time2,&time2)){
                                   cout<<"\n修改时间成功!\n";
                                 }
                else{
                       cout<<"修改时间失败!\n";
                    }
                }
  else{
  cout<<"时间转换失败！\n";
  }

  cout<<"时间:"<<systime.wYear<<"年"<<systime.wMonth<<"月"<<systime.wDay<<"日\n";
}
system("pause");
system("cls");
goto start;
return 0;
}