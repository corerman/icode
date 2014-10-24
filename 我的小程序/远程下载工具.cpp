/*
 * main.cpp
 *
 *  Created on: 2014-10-24
 *      Author: root
 */

#include<stdio.h>
#include<stdlib.h>

int main(){
	char web_link[200],save[200];
	printf("请输入网络文件链接地址：");
	scanf("%s",web_link);
	printf("请输入文件保存位置：");
	scanf("%s",save);
	FILE* f=fopen("/root/download.sh","w");
	fprintf(f,"cd %s\n",save);
	fprintf(f,"%s","wget ");
	fprintf(f,"%s",web_link);
	fclose(f);
	system("chmod 777 /root/download.sh");
	system("/root/download.sh");
	system("rm /root/download.sh");
return 0;
}


