struct grade{
	int correct;
	int total;
};

void CleanFile(char* NumOfProbelm){
	//构造删除目录
	char delfile[255];
	//构造通用目录
	char ComLocation[255];
	strcpy(ComLocation,"c:\\isave\\");
	//构造NumofProblem目录
	char NumLocation[255];
	strcpy(NumLocation,ComLocation);
	
	strcat(NumLocation,NumOfProbelm);
	strcat(NumLocation,"\\*");
	//	printf("%s\n",NumLocation);
	WIN32_FIND_DATA fileinfo;
	HANDLE FindFile=FindFirstFile(NumLocation,&fileinfo);
	while(FindNextFile(FindFile,&fileinfo)){
		strcpy(delfile,ComLocation);
		strcat(delfile,NumOfProbelm);
		strcat(delfile,"\\");
		strcat(delfile,fileinfo.cFileName);
		//	printf("%s\n",delfile);
		DeleteFile(delfile);
	}
	
	// 删除run目录文件
	strcpy(NumLocation,ComLocation);
	strcat(NumLocation,NumOfProbelm);
	strcat(NumLocation,"\\run\\*");
	//	printf("%s\n",NumLocation);
	FindFile=FindFirstFile(NumLocation,&fileinfo);
	while(FindNextFile(FindFile,&fileinfo)){
		strcpy(delfile,ComLocation);
		strcat(delfile,NumOfProbelm);
		strcat(delfile,"\\run\\");
		strcat(delfile,fileinfo.cFileName);
		//	printf("%s\n",delfile);
		DeleteFile(delfile);
	}
}

void InitWindow(){
	system("cls");
	system("title 评测系统");
	system("color 1f");
	system("mode con cols=60 lines=20");
}

int TestNetLink(){
//	printf("\n正在检测网络配置...\n\n");
	int result;
	DWORD NetStat;
	result=InternetGetConnectedState(&NetStat,0);
return result;
}


/*int TestNetLink(){   
	printf("\n正在检测网络配置...\n\n");
	system("ping baidu.com > c:\\Windows\\ping.txt");
	FILE* fcin=fopen("c:\\Windows\\ping.txt","r");
	char result[30];
	fscanf(fcin,"%s",result);
	fscanf(fcin,"%s",result);
	fclose(fcin);
	if(strcmp(result,"请求找不到主机")==0) return 0; 
	else return 1;
}*/

int IsFirst(){
	FILE* firstfile=fopen("C:\\Program Files\\FirstFlag.txt","r");
	if(firstfile==NULL) return 1;
	else return 0;
}

//下载比对文件
int DownCheckFile(char* NumOfProblem){
	//构造字符串
	int result=1;
	HRESULT hr;
	char address[255],eachsave[255],eachfile[255];
	strcpy(address,"http://iproblem.qiniudn.com/");
	strcat(address,NumOfProblem);
	strcat(address,".dat");
	//清除urldowntofile的缓存信息，参数完整的路径
	char szUrl[255]; 
	strcpy(szUrl,address);
	DeleteUrlCacheEntry (szUrl); 
	//在清除缓存后重新下载文件 
	CreateDirectory("c:\\isave",NULL);
	strcpy(eachsave,"c:\\isave\\");
	strcat(eachsave,NumOfProblem);
	CreateDirectory(eachsave,NULL);
	strcpy(eachfile,"c:\\isave\\");
	strcat(eachfile,NumOfProblem);
	strcat(eachfile,"\\");
	strcat(eachfile,NumOfProblem);
	strcat(eachfile,".dat");
	hr=URLDownloadToFile(NULL,address,eachfile,0,NULL);
	if(hr!=S_OK){
		printf("  错误: 没有在服务器上检测到此评测编号对应的匹配文件!\n");
		system("pause");
		return 0;
	}
return result;
}



//分割文件在程序模块完整执行后返回值为最后一组数据的序号值
int divfile(char* NumOfProblem){
	int result=1;
	char FileLocation[255]; //存储当前评测文件的完全路径
	strcpy(FileLocation,"c:\\isave\\");
	strcat(FileLocation,NumOfProblem);
	strcat(FileLocation,"\\");
	strcat(FileLocation,NumOfProblem);
	strcat(FileLocation,".dat");
//	printf("%s\n",FileLocation);
	FILE* fdiv=NULL,*FileTemp=NULL;
	fdiv=fopen(FileLocation,"r");
	if(fdiv==NULL){
		printf("  错误: 匹配文件丢失或损坏!\n");
		return 0;
	}
	//利用算法分割文件进入到相应的目录
	char DivFileLocation[255],TempDir[255],divnum[10]; //分割文件的项目
	strcpy(DivFileLocation,"c:\\isave\\");
	strcat(DivFileLocation,NumOfProblem);
	strcat(DivFileLocation,"\\");
	strcpy(TempDir,DivFileLocation); //记录每一次的文件目录
	
	char everyread=' ';
	int i=0,count=-1;
	while(fscanf(fdiv,"%c",&everyread)!=EOF){
		if(everyread=='#') //
		{
			fscanf(fdiv,"%c",&everyread); //忽略#后的换行
			i++;
			switch (i)
			{
				case 1:count++;
						strcpy(divnum,"0");
						strcpy(TempDir,DivFileLocation); 
						divnum[0]+=count;//构造题目分割数据的文件编号
						strcat(TempDir,divnum);
						strcat(TempDir,".in");
					//	printf("%s\n",TempDir);
						FileTemp=fopen(TempDir,"w");
						
						break;
					//文件编号加1 创建in的序号文件
				case 2:fclose(FileTemp);
						break;
					//关闭in的序号文件
				case 3:strcpy(divnum,"0");
					strcpy(TempDir,DivFileLocation); 
					divnum[0]+=count;
					strcat(TempDir,divnum);
					strcat(TempDir,".out");
				//	printf("%s\n",TempDir);
					FileTemp=fopen(TempDir,"w");
					break;
					//创建out的序号文件
				case 4: ;//归零i 关闭out的序号文件
					i=0;
					fclose(FileTemp);
					break;
			}
		}
		else{
			fprintf(FileTemp,"%c",everyread);
		}
	}
fclose(fdiv);
return count;
}


//编译源码文件
int  CompileFile(char* NumOfProgram){
	int result=1;
	//构造当前的源码文件
	char CurrentSource[255],checkexe[255];
	GetCurrentDirectory(255,CurrentSource);
	strcat(CurrentSource,"\\");
	strcat(CurrentSource,NumOfProgram);
	strcat(CurrentSource,".c");
	
	//构造评测数据目录地址
	char MoveDir[255];
	strcpy(MoveDir,"c:\\isave\\");
	strcat(MoveDir,NumOfProgram);
	strcat(MoveDir,"\\");
	strcat(MoveDir,NumOfProgram);
	strcat(MoveDir,".c");
	//	printf("%s\n",CurrentSource);
	//	printf("%s\n",MoveDir);
	if(!CopyFile(CurrentSource,MoveDir,false)){
		printf("  错误: 请查看%s.c源码文件是否存在!\n",NumOfProgram);
		CleanFile(NumOfProgram);
		return 0;
	}
	
	//构造编译目录 进行编译
	char gcclocation[255]="D:\\gcc\\bin\\gcc";
	char command[300];
	strcpy(command,gcclocation);
	strcat(command," ");
	strcat(command,NumOfProgram);
	strcat(command,".c ");
	strcat(command,"-o ");
	strcat(command,"c:\\isave\\");
	strcat(command,NumOfProgram);
	strcat(command,"\\");
	strcat(command,"debug.exe");
	system(command);
	strcpy(checkexe,"c:\\isave\\");
	strcat(checkexe,NumOfProgram);
	strcat(checkexe,"\\debug.exe");
//	printf("%s\n",checkexe);  exe文件路径
	FILE* fcheckexe=fopen(checkexe,"r"); //检测exe是否存在 存在则完美编译
	if(!fcheckexe){ printf("错误: 编译失败,请检查源码文件!\n"); return 0;};
	fclose(fcheckexe);
	return result;
}

//根据对应题号目录中的in文件  在run目录中输出相应的结果文件
int CreateRunResult(char* NumofProblem,int FileCount){
	int FileId,result=1;
	//构造通用的路径
	char ComLocation[255]; //每一个题号对应的目录 例如 c:\isave\1\;
	strcpy(ComLocation,"c:\\isave\\");
	strcat(ComLocation,NumofProblem);
	strcat(ComLocation,"\\");

	//根据题号构造EXE文件路径
	char LocationOfExe[255];
	strcpy(LocationOfExe,ComLocation);
	strcat(LocationOfExe,"debug.exe"); //每一个题号的根目录都有一个debug.exe 例如:c:\isave\1\debug.exe
	
	
	//创建保存运行结果的目录
	char Rundir[255];
	strcpy(Rundir,ComLocation);
	strcat(Rundir,"run\\");
	CreateDirectory(Rundir,NULL);
//	printf("%s\n",Rundir);
	//记录命令的字符串 例如: c:\isave\1\debug.exe <c:\isave\1\0.in >c:\isave\1\run\0.out 
	char command[255];

	//创建变化的run目录里面的out文件  创建命令中的in序号文件字符串
	char outs[10]="0.out",ins[10]="0.in";
	for(FileId=0;FileId<=FileCount;FileId++){
		ins[0]='0'+FileId;
		outs[0]='0'+FileId;
		strcpy(command,ComLocation);
		strcat(command,"debug.exe ");
		strcat(command,"<");
		strcat(command,ComLocation);
		strcat(command,ins);
		strcat(command," >");
		strcat(command,Rundir);
		strcat(command,outs);
		system(command);
	}
return result;
}


//传入两个文件的磁盘地址 如果相同返回1 不相同返回0  其他操作错误返回3;
//此版本为字符完全匹对函数 匹对空格等 忽略最后一行的换行
int CompFile(char* SourceFile, char* NewFile){
	int result=1,eof1=0,eof2=0;
	FILE *file1=NULL,*file2=NULL;
	file1=fopen(SourceFile,"r");
	if(file1==NULL){printf(" 错误：%s 不存在!\n",SourceFile); return 3;}; 
	file2=fopen(NewFile,"r");
	if(file2==NULL){ printf(" 错误：%s 不存在!\n",NewFile); return 3;}; 
	char StrOfFile1=' ',StrOfFile2=' ';
	while((fscanf(file1,"%c",&StrOfFile1)!=EOF)&&(fscanf(file2,"%c",&StrOfFile2)!=EOF)){
		if(StrOfFile1!=StrOfFile2){
			result=0;
			break;
		}	
	} 

	if((fscanf(file1,"%c",&StrOfFile1)!=EOF)||(fscanf(file2,"%c",&StrOfFile2)!=EOF))
		result=0;
	fclose(file1);
	fclose(file2);
	return result;		
}

struct grade CountGrade(char* NumofProblem,int NumOfCheckFile){
	struct grade Mygrade={0,0};
	//构造共同路径 ComLocation
	char ComLocation[255]; //每一个题号对应的目录 例如 c:\isave\1\;
	strcpy(ComLocation,"c:\\isave\\");
	strcat(ComLocation,NumofProblem);
	strcat(ComLocation,"\\");
	//构造两个目录 一个是源测试文件 一个是用户运行结果
	char source[255];
	char userrun[255];
	//定义比较的out文件名
	char outs[10]="0.out";
	int fileid;
	printf("\n                    评测结果\n");
	printf("             ========================\n");
	for(fileid=0;fileid<=NumOfCheckFile;fileid++){
		outs[0]='0'+fileid;
	//	printf("%s\n",outs);
		strcpy(source,"c:\\isave\\");
		strcat(source,NumofProblem);
		strcat(source,"\\");
		strcat(source,outs);
		strcpy(userrun,"c:\\isave\\");
		strcat(userrun,NumofProblem);
		strcat(userrun,"\\run\\");
		strcat(userrun,outs);
	//	printf("%s\n%s\n\n\n",source,userrun);
		if(CompFile(source,userrun))
		{
			Mygrade.correct++;
			printf("             ‖第%d组测试数据\t√ ‖\n",fileid+1);
		}
		else
		{
			printf("             ‖第%d组测试数据\t× ‖\n",fileid+1);
		}
		Mygrade.total++;

	}
		printf("             ========================\n");
return Mygrade;
}

int CheckUpdate(char* VersionOld){ //如果需要更新 则返回1 否则返回0
	int result=0;
	HRESULT hr;
	//清空缓存
	char szUrl[100] = "http://else.qiniudn.com/updateinfo.dat";  //为什么不用7牛的服务器 因为此文件会在7牛的云服务器上备份很多份，即使删除浏览器缓存也会再次成功下载
	// 清理缓存
	DeleteUrlCacheEntry (szUrl);
	hr=URLDownloadToFile(NULL,"http://else.qiniudn.com/updateinfo.dat","C:\\Program Files\\updateinfo.dat",0,0);
	if(hr==S_OK){
		FILE* fversion=fopen("C:\\Program Files\\updateinfo.dat","r");
		char VersionNew[20];
		fscanf(fversion,"%s",VersionNew);//第一行为版本号
		if(strcmp(VersionNew,VersionOld)){
			result=1;
			int select;
			select=MessageBox(NULL,"警告:\n  您当前使用的评测系统需要更新!\n  您是否选择现在更新?","更新提示",MB_YESNO+MB_ICONQUESTION);
			if(select==IDYES){
				//读取更新文件字符串 存入VersionNew
				fscanf(fversion,"%s",VersionNew);
				//构造下载文件地址
				char DownWay[100]="http://else.qiniudn.com/";
				strcat(DownWay,VersionNew);
				char SaveWay[100]="c:\\";
				strcat(SaveWay,VersionNew);
				//清除缓存
				DeleteUrlCacheEntry (DownWay);
				hr=URLDownloadToFile(NULL,DownWay,SaveWay,0,0);
				fclose(fversion);
				result=1;
				printf("\n提示: 更新已经完成!\n新版本的文件: %s 已经存放在了C盘!\n",VersionNew);
				system("start c:\\");
				DeleteFile("C:\\Program Files\\updateinfo.dat");
				system("pause");
				exit(0);
			}
			else
			{
				exit(0);
			}
		}
	}
	else result=0;
return result;
}
 
int ViewProblems(char* NumOfProblem){ //如果选择查看 返回1  如果不查看 返回0
	int charcount=0;
	int select;
	select=MessageBox(NULL,"您是否需要查看题目信息?","查看题目",MB_YESNO+MB_ICONQUESTION);
	if(select==IDYES)
	{
		//构造题号路径
		char UrlLocation[100]="http://iproblem.qiniudn.com/";
		strcat(UrlLocation,NumOfProblem);
		strcat(UrlLocation,".txt"); //构造下载源路径完毕
	//	printf("%s\n",UrlLocation);
		//构造保存路径
		char SaveLocation[100]="c:\\isave\\";
		strcat(SaveLocation,NumOfProblem);
		//strcat(SaveLocation,"\\");
	//	strcat(SaveLocation,NumOfProblem);
		strcat(SaveLocation,".txt"); //构造保存路径完毕
		//构造下载
		HRESULT hr;
		DeleteUrlCacheEntry(UrlLocation);
		hr=URLDownloadToFile(NULL,UrlLocation,SaveLocation,0,0);
		if(hr==S_OK){
		system("cls");
		char temp;
		FILE* fread=fopen(SaveLocation,"r");
		while(fscanf(fread,"%c",&temp)!=EOF){
			charcount++;
			if(charcount>300){
				system("cls");
				fclose(fread);
				ShellExecute(NULL,"open",SaveLocation,NULL,NULL,SW_SHOWNORMAL);
				break;
			}
			printf("%c",temp);
		}
		fclose(fread);
		}
		select=1;
		
	}
	else
	{
		select=0;	
	}
return select;
}