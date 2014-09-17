#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<Wininet.h>
#include <UrlMon.h>
#include "JudgeFunc.h"
#pragma comment(lib,"urlmon.lib")


#pragma comment (lib,"Wininet.lib")
int main(){
	char VersionOld[20]="1.0.1"; //当前程序的版本号,需要随着更新版本而修改。
	//1.初始化界面
	InitWindow();
	printf("\n正在检测相关配置....\n\n");
	while(!TestNetLink()){ printf("  错误:无网络连接,请连接网络!\n\n"); system("pause"); return 0;}//网络连接判断
	printf("  提示:网络运行状况正常!\n");


	CheckUpdate(VersionOld);
	//配置GCC环境
	if(IsFirst()){ printf("\n  您这是是第一次使用评测系统,我们将为您配置GCC编译环境!\n\n");
		system("pause");
		ShellExecute(NULL,"open","SetGcc.exe",NULL,NULL,SW_NORMAL);
		FILE* ftest=NULL;
		ftest=fopen("C:\\Program Files\\FirstFlag.txt","r");
		while(!ftest){
				ftest=fopen("C:\\Program Files\\FirstFlag.txt","r");
		}
	}
	//配置GCC环境结束
	
	// 1.下载比对文件并分割文件
	char NumOfProblem[200];
	int downresult;
	printf("========================");
cinnum:
	printf("\n请输入评测编号:");
	scanf("%s",NumOfProblem);
	downresult=DownCheckFile(NumOfProblem);
	if(!downresult){
		system("cls");
		goto cinnum;
	} //下载文件完成

	//询问用户是否需要查看题目 如果需要下载题目
	if(ViewProblems(NumOfProblem)){
		printf("\n");
		system("pause");
		system("cls");
		goto cinnum;
	}


	//分割文件 参数:NumOfProblem 题目编号
	int NumOfCheckFile;
	NumOfCheckFile=divfile(NumOfProblem); //分割文件完毕

	//编译文件
	if(!CompileFile(NumOfProblem)){
		system("pause");
		system("cls");
		goto cinnum;
	}//编译文件完毕

	//生成自我匹配文件 放在相应题号目录中的run文件夹中 利用参数 1. 题号 2.文件的序号个数从0开始计数 
	CreateRunResult(NumOfProblem,NumOfCheckFile);

	//比较结果进行计分处理
	//这个函数需要两个参数 传进去一个题号NumOfProblem  传进去一个文件数 返回一个结构体 正确测试数 总测试数
	struct grade MyGrade;
	system("cls");
	MyGrade=CountGrade(NumOfProblem,NumOfCheckFile);
	printf("             ========================\n");
	printf("                 总分:%d\n",MyGrade.total*10);
	printf("                 您本次成绩:%d\n",MyGrade.correct*10);
	printf("             ========================\n");
	CleanFile(NumOfProblem);
	system("pause");
	system("cls");
	//清除目录内所有文件

	goto cinnum;
return 0;
}