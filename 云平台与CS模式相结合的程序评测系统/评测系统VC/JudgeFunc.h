struct grade{
	int correct;
	int total;
};

void CleanFile(char* NumOfProbelm){
	//����ɾ��Ŀ¼
	char delfile[255];
	//����ͨ��Ŀ¼
	char ComLocation[255];
	strcpy(ComLocation,"c:\\isave\\");
	//����NumofProblemĿ¼
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
	
	// ɾ��runĿ¼�ļ�
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
	system("title ����ϵͳ");
	system("color 1f");
	system("mode con cols=60 lines=20");
}

int TestNetLink(){
//	printf("\n���ڼ����������...\n\n");
	int result;
	DWORD NetStat;
	result=InternetGetConnectedState(&NetStat,0);
return result;
}


/*int TestNetLink(){   
	printf("\n���ڼ����������...\n\n");
	system("ping baidu.com > c:\\Windows\\ping.txt");
	FILE* fcin=fopen("c:\\Windows\\ping.txt","r");
	char result[30];
	fscanf(fcin,"%s",result);
	fscanf(fcin,"%s",result);
	fclose(fcin);
	if(strcmp(result,"�����Ҳ�������")==0) return 0; 
	else return 1;
}*/

int IsFirst(){
	FILE* firstfile=fopen("C:\\Program Files\\FirstFlag.txt","r");
	if(firstfile==NULL) return 1;
	else return 0;
}

//���رȶ��ļ�
int DownCheckFile(char* NumOfProblem){
	//�����ַ���
	int result=1;
	HRESULT hr;
	char address[255],eachsave[255],eachfile[255];
	strcpy(address,"http://iproblem.qiniudn.com/");
	strcat(address,NumOfProblem);
	strcat(address,".dat");
	//���urldowntofile�Ļ�����Ϣ������������·��
	char szUrl[255]; 
	strcpy(szUrl,address);
	DeleteUrlCacheEntry (szUrl); 
	//�������������������ļ� 
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
		printf("  ����: û���ڷ������ϼ�⵽�������Ŷ�Ӧ��ƥ���ļ�!\n");
		system("pause");
		return 0;
	}
return result;
}



//�ָ��ļ��ڳ���ģ������ִ�к󷵻�ֵΪ���һ�����ݵ����ֵ
int divfile(char* NumOfProblem){
	int result=1;
	char FileLocation[255]; //�洢��ǰ�����ļ�����ȫ·��
	strcpy(FileLocation,"c:\\isave\\");
	strcat(FileLocation,NumOfProblem);
	strcat(FileLocation,"\\");
	strcat(FileLocation,NumOfProblem);
	strcat(FileLocation,".dat");
//	printf("%s\n",FileLocation);
	FILE* fdiv=NULL,*FileTemp=NULL;
	fdiv=fopen(FileLocation,"r");
	if(fdiv==NULL){
		printf("  ����: ƥ���ļ���ʧ����!\n");
		return 0;
	}
	//�����㷨�ָ��ļ����뵽��Ӧ��Ŀ¼
	char DivFileLocation[255],TempDir[255],divnum[10]; //�ָ��ļ�����Ŀ
	strcpy(DivFileLocation,"c:\\isave\\");
	strcat(DivFileLocation,NumOfProblem);
	strcat(DivFileLocation,"\\");
	strcpy(TempDir,DivFileLocation); //��¼ÿһ�ε��ļ�Ŀ¼
	
	char everyread=' ';
	int i=0,count=-1;
	while(fscanf(fdiv,"%c",&everyread)!=EOF){
		if(everyread=='#') //
		{
			fscanf(fdiv,"%c",&everyread); //����#��Ļ���
			i++;
			switch (i)
			{
				case 1:count++;
						strcpy(divnum,"0");
						strcpy(TempDir,DivFileLocation); 
						divnum[0]+=count;//������Ŀ�ָ����ݵ��ļ����
						strcat(TempDir,divnum);
						strcat(TempDir,".in");
					//	printf("%s\n",TempDir);
						FileTemp=fopen(TempDir,"w");
						
						break;
					//�ļ���ż�1 ����in������ļ�
				case 2:fclose(FileTemp);
						break;
					//�ر�in������ļ�
				case 3:strcpy(divnum,"0");
					strcpy(TempDir,DivFileLocation); 
					divnum[0]+=count;
					strcat(TempDir,divnum);
					strcat(TempDir,".out");
				//	printf("%s\n",TempDir);
					FileTemp=fopen(TempDir,"w");
					break;
					//����out������ļ�
				case 4: ;//����i �ر�out������ļ�
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


//����Դ���ļ�
int  CompileFile(char* NumOfProgram){
	int result=1;
	//���쵱ǰ��Դ���ļ�
	char CurrentSource[255],checkexe[255];
	GetCurrentDirectory(255,CurrentSource);
	strcat(CurrentSource,"\\");
	strcat(CurrentSource,NumOfProgram);
	strcat(CurrentSource,".c");
	
	//������������Ŀ¼��ַ
	char MoveDir[255];
	strcpy(MoveDir,"c:\\isave\\");
	strcat(MoveDir,NumOfProgram);
	strcat(MoveDir,"\\");
	strcat(MoveDir,NumOfProgram);
	strcat(MoveDir,".c");
	//	printf("%s\n",CurrentSource);
	//	printf("%s\n",MoveDir);
	if(!CopyFile(CurrentSource,MoveDir,false)){
		printf("  ����: ��鿴%s.cԴ���ļ��Ƿ����!\n",NumOfProgram);
		CleanFile(NumOfProgram);
		return 0;
	}
	
	//�������Ŀ¼ ���б���
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
//	printf("%s\n",checkexe);  exe�ļ�·��
	FILE* fcheckexe=fopen(checkexe,"r"); //���exe�Ƿ���� ��������������
	if(!fcheckexe){ printf("����: ����ʧ��,����Դ���ļ�!\n"); return 0;};
	fclose(fcheckexe);
	return result;
}

//���ݶ�Ӧ���Ŀ¼�е�in�ļ�  ��runĿ¼�������Ӧ�Ľ���ļ�
int CreateRunResult(char* NumofProblem,int FileCount){
	int FileId,result=1;
	//����ͨ�õ�·��
	char ComLocation[255]; //ÿһ����Ŷ�Ӧ��Ŀ¼ ���� c:\isave\1\;
	strcpy(ComLocation,"c:\\isave\\");
	strcat(ComLocation,NumofProblem);
	strcat(ComLocation,"\\");

	//������Ź���EXE�ļ�·��
	char LocationOfExe[255];
	strcpy(LocationOfExe,ComLocation);
	strcat(LocationOfExe,"debug.exe"); //ÿһ����ŵĸ�Ŀ¼����һ��debug.exe ����:c:\isave\1\debug.exe
	
	
	//�����������н����Ŀ¼
	char Rundir[255];
	strcpy(Rundir,ComLocation);
	strcat(Rundir,"run\\");
	CreateDirectory(Rundir,NULL);
//	printf("%s\n",Rundir);
	//��¼������ַ��� ����: c:\isave\1\debug.exe <c:\isave\1\0.in >c:\isave\1\run\0.out 
	char command[255];

	//�����仯��runĿ¼�����out�ļ�  ���������е�in����ļ��ַ���
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


//���������ļ��Ĵ��̵�ַ �����ͬ����1 ����ͬ����0  �����������󷵻�3;
//�˰汾Ϊ�ַ���ȫƥ�Ժ��� ƥ�Կո�� �������һ�еĻ���
int CompFile(char* SourceFile, char* NewFile){
	int result=1,eof1=0,eof2=0;
	FILE *file1=NULL,*file2=NULL;
	file1=fopen(SourceFile,"r");
	if(file1==NULL){printf(" ����%s ������!\n",SourceFile); return 3;}; 
	file2=fopen(NewFile,"r");
	if(file2==NULL){ printf(" ����%s ������!\n",NewFile); return 3;}; 
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
	//���칲ͬ·�� ComLocation
	char ComLocation[255]; //ÿһ����Ŷ�Ӧ��Ŀ¼ ���� c:\isave\1\;
	strcpy(ComLocation,"c:\\isave\\");
	strcat(ComLocation,NumofProblem);
	strcat(ComLocation,"\\");
	//��������Ŀ¼ һ����Դ�����ļ� һ�����û����н��
	char source[255];
	char userrun[255];
	//����Ƚϵ�out�ļ���
	char outs[10]="0.out";
	int fileid;
	printf("\n                    ������\n");
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
			printf("             ����%d���������\t�� ��\n",fileid+1);
		}
		else
		{
			printf("             ����%d���������\t�� ��\n",fileid+1);
		}
		Mygrade.total++;

	}
		printf("             ========================\n");
return Mygrade;
}

int CheckUpdate(char* VersionOld){ //�����Ҫ���� �򷵻�1 ���򷵻�0
	int result=0;
	HRESULT hr;
	//��ջ���
	char szUrl[100] = "http://else.qiniudn.com/updateinfo.dat";  //Ϊʲô����7ţ�ķ����� ��Ϊ���ļ�����7ţ���Ʒ������ϱ��ݺܶ�ݣ���ʹɾ�����������Ҳ���ٴγɹ�����
	// ������
	DeleteUrlCacheEntry (szUrl);
	hr=URLDownloadToFile(NULL,"http://else.qiniudn.com/updateinfo.dat","C:\\Program Files\\updateinfo.dat",0,0);
	if(hr==S_OK){
		FILE* fversion=fopen("C:\\Program Files\\updateinfo.dat","r");
		char VersionNew[20];
		fscanf(fversion,"%s",VersionNew);//��һ��Ϊ�汾��
		if(strcmp(VersionNew,VersionOld)){
			result=1;
			int select;
			select=MessageBox(NULL,"����:\n  ����ǰʹ�õ�����ϵͳ��Ҫ����!\n  ���Ƿ�ѡ�����ڸ���?","������ʾ",MB_YESNO+MB_ICONQUESTION);
			if(select==IDYES){
				//��ȡ�����ļ��ַ��� ����VersionNew
				fscanf(fversion,"%s",VersionNew);
				//���������ļ���ַ
				char DownWay[100]="http://else.qiniudn.com/";
				strcat(DownWay,VersionNew);
				char SaveWay[100]="c:\\";
				strcat(SaveWay,VersionNew);
				//�������
				DeleteUrlCacheEntry (DownWay);
				hr=URLDownloadToFile(NULL,DownWay,SaveWay,0,0);
				fclose(fversion);
				result=1;
				printf("\n��ʾ: �����Ѿ����!\n�°汾���ļ�: %s �Ѿ��������C��!\n",VersionNew);
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
 
int ViewProblems(char* NumOfProblem){ //���ѡ��鿴 ����1  ������鿴 ����0
	int charcount=0;
	int select;
	select=MessageBox(NULL,"���Ƿ���Ҫ�鿴��Ŀ��Ϣ?","�鿴��Ŀ",MB_YESNO+MB_ICONQUESTION);
	if(select==IDYES)
	{
		//�������·��
		char UrlLocation[100]="http://iproblem.qiniudn.com/";
		strcat(UrlLocation,NumOfProblem);
		strcat(UrlLocation,".txt"); //��������Դ·�����
	//	printf("%s\n",UrlLocation);
		//���챣��·��
		char SaveLocation[100]="c:\\isave\\";
		strcat(SaveLocation,NumOfProblem);
		//strcat(SaveLocation,"\\");
	//	strcat(SaveLocation,NumOfProblem);
		strcat(SaveLocation,".txt"); //���챣��·�����
		//��������
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