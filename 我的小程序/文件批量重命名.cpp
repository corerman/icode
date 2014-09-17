#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
using namespace std;


int  main()
	{
		system("title 批量重命名---中国深点科技");
		system("color a");
		cout<<"\n使用需知:\n\n   1.  此软件用于批量重命名文件.\n   2.  [原文件的文件名顺序即修改后的文件顺序].\n\n";
		int filelist(char formname[]);
		char formname[5];
		cout<<"请输入文件格式名(例如:exe):";
		cin>>formname;
		if(filelist(formname))
		{
			cout<<"\n\n运行提示:成功转换所有文件名称!\n\n";
		}
		else
		{
			cout<<"运行提示:转换命令执行失败,请检查上面显示的返回信息,筛选错误项!\n";
		}
system("pause");
return 0;
	}


int filelist(char formname[])
	{
		int count=0;
		char name3[MAX_PATH];
		string name31;
		char name[20];
		cout<<"请输入新文件名:";
		cin>>name;
		char pathway[MAX_PATH];
		string path2;
		DWORD len=MAX_PATH;
		if(GetCurrentDirectory(len,pathway))
			{
				path2=pathway;
				LPSTR fileskey;
				fileskey=lstrcat(pathway,"\\*.");
				fileskey=lstrcat(fileskey,formname);
				HANDLE findfile;
				WIN32_FIND_DATA filedata;
				findfile=FindFirstFile(fileskey,&filedata);
				void   read_line1(char   line[]);
				void   read_line2(char   line[]);
				char oldname[MAX_PATH];
				char newname[MAX_PATH];
				if(findfile)
					{
						if(count==0)
							{
								void   read_line2(char   line[]);
								ofstream solveprogram("c:\\name2.txt");
								solveprogram<<path2<<"\\"<<name<<'0'<<'.'<<formname;
								solveprogram.close();
								read_line2(name3);
								name31=name3;
							}
						
						int result=1;
						while(result)
							{
								ofstream outfile1("c:\\name1.txt");
				                ofstream outfile2("c:\\name2.txt");
								outfile1<<path2<<"\\"<<filedata.cFileName;
								outfile2<<path2<<"\\"<<name<<count<<"."<<formname;
								outfile1.close();
								outfile2.close();
								Sleep(10);
								read_line1(oldname);
								read_line2(newname);
								if((oldname==name31)&&(count!=0))
								{
									return 1;
								}
								if(MoveFile(oldname,newname))
									{
										cout<<"成功操作:"<<oldname<<'\n';
									}
								else
									{
										cout<<"操作【"<<oldname<<"】失败\n";
									}
								        count++;
									    result=FindNextFile(findfile,&filedata);
										//system("pause");
								}
						
						      	
						   }

			
		 	}
		return 1;
	}


void   read_line1(char   line[])  
{  
    FILE   *fp;  
    char   cChar;  
    int   i;  
    fp=fopen("c:\\name1.txt","r");  
    i=0;  
    cChar=fgetc(fp);  
    while(cChar!='\n'   &&   !feof(fp))  
    {  
        line[i]=cChar;  
        i++;  
        cChar=fgetc(fp);  
    }  
    line[i]='\0';  
    return;  
}
void   read_line2(char   line[])  
{  
    FILE   *fp;  
    char   cChar;  
    int   i;  
    fp=fopen("c:\\name2.txt","r");  
    i=0;  
    cChar=fgetc(fp);  
    while(cChar!='\n'   &&   !feof(fp))  
    {  
        line[i]=cChar;  
        i++;  
        cChar=fgetc(fp);  
    }  
    line[i]='\0';  
    return;  
}