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
	system("title 正在为您配置GCC编译环境...");
	while(!TestNetLink()){ printf("请连接网络!\n"); system("pause");}
	printf("注意: 保存目录为 D:\\gcc   请勿删除!\n\n");
//	system("pause");
	int result=0;
	result=CreatDir();
	while(!result) ;
	int command;
	printf("选择菜单:\n  1.快速配置Gcc环境\n");
	printf("  2.兼容性配置Gcc环境\n");
	printf("\n输入操作编号:");
	scanf("%d",&command);
	if(command==1){
		QuickCreateGcc();
		printf("\n环境配置完毕!\n");
		system("pause");
	}
	else{
		HRESULT hr=NULL;
		DownloadFile(hr);
		printf("\n环境配置完毕!\n");
		system("pause");
	}
CreateFile("C:\\Program Files\\FirstFlag.txt",GENERIC_READ,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
return 0;
}