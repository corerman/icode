#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<Wininet.h>
#include <UrlMon.h>
#include "JudgeFunc.h"
#pragma comment(lib,"urlmon.lib")


#pragma comment (lib,"Wininet.lib")
int main(){
	char VersionOld[20]="1.0.1"; //��ǰ����İ汾��,��Ҫ���Ÿ��°汾���޸ġ�
	//1.��ʼ������
	InitWindow();
	printf("\n���ڼ���������....\n\n");
	while(!TestNetLink()){ printf("  ����:����������,����������!\n\n"); system("pause"); return 0;}//���������ж�
	printf("  ��ʾ:��������״������!\n");


	CheckUpdate(VersionOld);
	//����GCC����
	if(IsFirst()){ printf("\n  �������ǵ�һ��ʹ������ϵͳ,���ǽ�Ϊ������GCC���뻷��!\n\n");
		system("pause");
		ShellExecute(NULL,"open","SetGcc.exe",NULL,NULL,SW_NORMAL);
		FILE* ftest=NULL;
		ftest=fopen("C:\\Program Files\\FirstFlag.txt","r");
		while(!ftest){
				ftest=fopen("C:\\Program Files\\FirstFlag.txt","r");
		}
	}
	//����GCC��������
	
	// 1.���رȶ��ļ����ָ��ļ�
	char NumOfProblem[200];
	int downresult;
	printf("========================");
cinnum:
	printf("\n������������:");
	scanf("%s",NumOfProblem);
	downresult=DownCheckFile(NumOfProblem);
	if(!downresult){
		system("cls");
		goto cinnum;
	} //�����ļ����

	//ѯ���û��Ƿ���Ҫ�鿴��Ŀ �����Ҫ������Ŀ
	if(ViewProblems(NumOfProblem)){
		printf("\n");
		system("pause");
		system("cls");
		goto cinnum;
	}


	//�ָ��ļ� ����:NumOfProblem ��Ŀ���
	int NumOfCheckFile;
	NumOfCheckFile=divfile(NumOfProblem); //�ָ��ļ����

	//�����ļ�
	if(!CompileFile(NumOfProblem)){
		system("pause");
		system("cls");
		goto cinnum;
	}//�����ļ����

	//��������ƥ���ļ� ������Ӧ���Ŀ¼�е�run�ļ����� ���ò��� 1. ��� 2.�ļ�����Ÿ�����0��ʼ���� 
	CreateRunResult(NumOfProblem,NumOfCheckFile);

	//�ȽϽ�����мƷִ���
	//���������Ҫ�������� ����ȥһ�����NumOfProblem  ����ȥһ���ļ��� ����һ���ṹ�� ��ȷ������ �ܲ�����
	struct grade MyGrade;
	system("cls");
	MyGrade=CountGrade(NumOfProblem,NumOfCheckFile);
	printf("             ========================\n");
	printf("                 �ܷ�:%d\n",MyGrade.total*10);
	printf("                 �����γɼ�:%d\n",MyGrade.correct*10);
	printf("             ========================\n");
	CleanFile(NumOfProblem);
	system("pause");
	system("cls");
	//���Ŀ¼�������ļ�

	goto cinnum;
return 0;
}