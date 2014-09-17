#include<iostream>
#include<windows.h>
using namespace std;

int main(){
	
	int num=0;//定义移动量;
	DWORD driver;//定义驱动器列表变量;
	DWORD num2=0;//定义右移后储存变量;
	char a='A'; //定义初始驱动器;
	int  i=0;//定义增加变量;
	char drivelist[40];//定义驱动器列表;
    driver=GetLogicalDrives();
	if(driver){
	  while(num<=32){
	         num2=driver;
			 num2=num2>>num;//变量是从低二进制位开始填充的;
			 if((!(num2&1))&&(num>=2)){
			     cout<<"\n驱动器列表完成!\n\n";
				 break;
			 }
			 else
				 if(num2&1){
			     drivelist[i]=a+i;
			 }
			 i++;
			 num++;
          
	  }

	}
	else{
	  cout<<"驱动器列表获取失败!";
	}
int listnum=0;
listnum=sizeof(drivelist)/sizeof(char);
for(int a=0;a<listnum;a++){
	if((drivelist[a]>='A')&&(drivelist[a]<='Z')){
	cout<<"存在驱动器:  ["<<drivelist[a]<<"]\n";
	}
}
cout<<"\n\n";
system("pause");
return 0;

}