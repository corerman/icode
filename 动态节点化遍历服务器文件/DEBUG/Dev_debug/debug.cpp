#include<stdio.h>

int JudgeSort(int* numlist,int count);
int main(){
	int a[100];
	int i=0;
	while(scanf("%d",&a[i])!=EOF)
		i++; 
	if(JudgeSort(a,i)==2)
		printf("无序!\n");
	else
		printf("有序!\n");
return 0;		
}

int JudgeSort(int* numlist,int count){
	if(count<2) //如果只有一个元素 直接有序 
		return 0;
	int flag=1;
	if(numlist[0]-numlist[1]<0)
		flag=-1; //记录符号位
	int a;
	for(a=1;a<count-1;a++){
		if((numlist[a]-numlist[a+1])/flag<0) //如果与预先存储的符号位异号 则无序  
			break;
	}
	if(count-a!=1)
		return 2;
	return 0;
}
