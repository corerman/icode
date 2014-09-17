#include<iostream>
#include<windows.h>
using namespace std;

int main()
{
	HWND win;color
	system(" a");
	system("mode con:cols=20 lines=5");
	SetConsoleTitle("自动连接");
	POINT xy;
	win=FindWindow(NULL,"自动连接");
	Sleep(50);
	GetCursorPos(&xy);
start:
	RECT winrec;
	win=FindWindow(NULL,"自动连接");
	ShowWindow(win,SW_HIDE);
	system("cls");
	cout<<"正在建立连接...";
	win=FindWindow(NULL,"iNode智能客户端");
	if(win)
	{
	GetWindowRect(win,&winrec);
	SetWindowPos(win,HWND_TOPMOST,winrec.left,winrec.top,0,0,SWP_NOSIZE);
	Sleep(20);
	SetCursorPos(winrec.left+249,winrec.top+119);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	Sleep(20);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	Sleep(20);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	Sleep(20);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

	start2:   win=FindWindow(NULL,"我的802.1X连接");
			  if(win)
			  {
				Sleep(50);
                GetWindowRect(win,&winrec);
				SetWindowPos(win,HWND_TOPMOST,winrec.left,winrec.top,0,0,SWP_NOSIZE);
				Sleep(20);
				SetCursorPos(winrec.left+85,winrec.top+355);
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				Sleep(20);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			  }
			  else
			  {
				  goto start2;
			  }

	}
	else
	{
		goto start;
	}
SetCursorPos(xy.x,xy.y);
return 0;
}