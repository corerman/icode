//密码加密部分

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>


struct bitChar{
	char* location;
}; 

		if(result[i])

//	system("pause");
	return 0; 
}

void CoverPassword(struct bitChar* bitinfo,char* password){
	//获取结构体中的数据
	int id=-1,i;
	while(*password) //遍历字符 
	{
		if(bitinfo[*password].location==NULL)
		{
			bitinfo[*password].location=(char*)malloc(sizeof(char)*16);
			for(i=0;i<16;i++)
				bitinfo[*password].location[i]=0;//位置信息清空
		}
		id++;
		bitinfo[*password].location[id]=1;
		password++;	 	 
	} 
}

void CreatePassword(struct bitChar* bitinfo,unsigned int* result){
	int i,i2,temp,temp2,i3;

				
			}
			result[i]=temp; 
		}
	}
}
