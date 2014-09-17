#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<SHELLAPI.H>
#include<shlobj.h>
#pragma comment("lib","shell32.lib")
using namespace std;

int main()
{
 char szcommandeline[MAX_PATH];
 SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
 SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL);
 SHChangeNotify(SHCNE_DELETE,SHCNF_PATH,_pgmptr,NULL);
 sprintf(szcommandeline,"/c del /q %s",_pgmptr);
 ShellExecute(NULL,"open","cmd.exe",szcommandeline,NULL,SW_HIDE);
 ExitProcess(0);
return 0;
}