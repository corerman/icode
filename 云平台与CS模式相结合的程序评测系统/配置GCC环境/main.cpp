#include<Windows.h>
#include<stdio.h>
#include<stdio.h>
#include<Wininet.h>
#include <UrlMon.h>
#include "gccfunc.h"
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"Wininet.lib")

int main(){
	system("mode con cols=35 lines=20");
	system("color 1F");
	system("title ����Ϊ������GCC���뻷��...");
	while(!TestNetLink()){ printf("����������!\n"); system("pause");}
	printf("ע��: ����Ŀ¼Ϊ D:\\gcc   ����ɾ��!\n\n");
//	system("pause");
	int result=0;
	result=CreatDir();
	while(!result) ;
	int command;
	printf("ѡ��˵�:\n  1.��������Gcc����\n");
	printf("  2.����������Gcc����\n");
	printf("\n����������:");
	scanf("%d",&command);
	if(command==1){
		QuickCreateGcc();
		printf("\n�����������!\n");
		system("pause");
	}
	else{
		HRESULT hr=NULL;
		DownloadFile(hr);
		printf("\n�����������!\n");
		system("pause");
	}
CreateFile("C:\\Program Files\\FirstFlag.txt",GENERIC_READ,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
return 0;
}