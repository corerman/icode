#include<stdio.h>

int JudgeSort(int* numlist,int count);
int main(){
	int a[100];
	int i=0;
	while(scanf("%d",&a[i])!=EOF)
		i++; 
	if(JudgeSort(a,i)==2)
		printf("����!\n");
	else
		printf("����!\n");
return 0;		
}

int JudgeSort(int* numlist,int count){
	if(count<2) //���ֻ��һ��Ԫ�� ֱ������ 
		return 0;
	int flag=1;
	if(numlist[0]-numlist[1]<0)
		flag=-1; //��¼����λ
	int a;
	for(a=1;a<count-1;a++){
		if((numlist[a]-numlist[a+1])/flag<0) //�����Ԥ�ȴ洢�ķ���λ��� ������  
			break;
	}
	if(count-a!=1)
		return 2;
	return 0;
}
