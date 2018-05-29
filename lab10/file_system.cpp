#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UserNumber 10       //用户数
#define UserFNumber 10      //用户文件数
#define OpenOFNumber 5

struct fname
{
    char fname[1];
    int flag;
} fnameA[26]={'a', 0, 'b', 0, 'c', 0, 'd', 0, 'e', 0, 'f', 0, 'g', 0, 'h', 0,
'i', 0, 'j', 0, 'k', 0, 'l', 0, 'm', 0, 'n', 0, 'o', 0, 'p', 0, 'q', 0, 'r', 0,
's', 0, 't', 0, 'u', 0, 'v', 0, 'w', 0, 'x', 0, 'y', 0, 'z', 0};

struct afd
{
   char opname[10];
   int flag;
   char opfprotect[3];
   int rwpoint;
} AFD[OpenOFNumber];

typedef struct
{
   char fname[10];
   int flag;
   int fprotect[3];
   int flength;
} ufd, UF[UserFNumber];

struct mdf
{
   char uname[10];
   UF Udir;
} UFD[UserNumber];

void intFSystem()
{
   int i, j, k, l;
   strcpy(UFD[0].uname, "user1");
   strcpy(UFD[1].uname, "Geogre");
   strcpy(UFD[2].uname, "user2");
   strcpy(UFD[3].uname, "Yiding");
   strcpy(UFD[4].uname, "Shadow");
   strcpy(UFD[5].uname, "user3");
   strcpy(UFD[6].uname, "user4");
   strcpy(UFD[7].uname, "user5");
   strcpy(UFD[8].uname, "user_6");
   strcpy(UFD[9].uname, "user");
   for (i=0; i<10; ++i)
   {
    for(k=0; k<5; ++k)
    {
        do j=rand()%26;
        while(fnameA[j].flag);
        strcpy(UFD[i].Udir[k].fname, fnameA[j].fname);
        fnameA[j].flag = 1;
        UFD[i].Udir[k].flength=rand()%2048+1;
        UFD[i].Udir[k].flag=1;
        UFD[i].Udir[k].fprotect[0]=rand()%2;
        UFD[i].Udir[k].fprotect[1]=rand()%2;
        UFD[i].Udir[k].fprotect[2]=rand()%2;
    }
    for (j=0; j<26; ++j)
    {
        fnameA[j].flag=0;
    }
}
for (l=0; l<5; ++l)
{
   strcpy(AFD[i].opname, "");
   AFD[l].flag=0;
   AFD[l].opfprotect[0]=0;
   AFD[l].opfprotect[1]=0;
   AFD[l].opfprotect[2]=0;
   AFD[l].rwpoint=0;
}
}

void Open(int i){
   int l, k, n;
   char file[10];
   for (l=0; l<5; ++l)
   {
       if(!AFD[l].flag)
       {
           break;
       }
   }
   if (l>=5) l=0;
   printf("Please enter file name :");
   scanf("%s", file);
   for (n=0; n<5; ++n){
       if(!strcmp(AFD[n].opname, file) && AFD[n].flag) {
           strcpy(AFD[l].opname, UFD[i].Udir[k].fname);
           AFD[l].opfprotect[0]=UFD[i].Udir[k].fprotect[0];
           AFD[l].opfprotect[1]=UFD[i].Udir[k].fprotect[1];
           AFD[l].opfprotect[2]=UFD[i].Udir[k].fprotect[2];
           AFD[l].flag=l;
           printf("file has opened!\n");
           return ;
       }
   }
   for (k=0; k<10; ++k)
   {
    if (!strcmp(UFD[i].Udir[k].fname, file) && UFD[i].Udir[k].flag)
    {
      strcpy(AFD[l].opname, UFD[i].Udir[k].fname);
      AFD[l].opfprotect[0]=UFD[i].Udir[k].fprotect[0];
      AFD[l].opfprotect[1]=UFD[i].Udir[k].fprotect[1];
      AFD[l].opfprotect[2]=UFD[i].Udir[k].fprotect[2];
      AFD[l].flag = 1;
      printf("file has open\n");
      return ;
  }
}
printf("file does not exist!\n");
return ;
}

void Create(int i)
{
   int k;
   for (k=0; k<10; ++k)
   {
       if(!UFD[i].Udir[k].flag)
        break;
}
if(k>=10)
{
   printf("A user cannot have more than 10 files\n\n");
   return ;
}
printf("Please enter file name :");
scanf("%s", UFD[i].Udir[k].fname);
printf("Please enter file length :");
scanf("%d", &UFD[i].Udir[k].flength);
printf("Read Only?(1 yes, 0 no):");
scanf("%d", &UFD[i].Udir[k].fprotect[0]);
printf("Write Only?(1 yes, 0 no):");
scanf("%d", &UFD[i].Udir[k].fprotect[1]);
printf("Execute?(1 yes, 0 no):");
scanf("%d", &UFD[i].Udir[k].fprotect[2]);
UFD[i].Udir[k].flag=1;
return ;
}

void Delete(int i)
{
   char file[10];
   int k;
   printf("Please enter the name of the file you want to delete :");
   scanf("%s", file);
   for (k=0; k<10; ++k){
       if(UFD[i].Udir[k].flag && !strcmp(UFD[i].Udir[k].fname, file))
       {
           UFD[i].Udir[k].flag=0;
           printf("file has deleted!\n");
           break;
       }
       else if(!UFD[i].Udir[k].flag && !strcmp(UFD[i].Udir[k].fname, file))
       {
           printf("file does not exist!\n");
       }
   }
   return ;
}

void Read()
{
   int l;
   char file[10];
   printf("Please enter file name:");
   scanf("%s", file);
   for (l=0; l<5; ++l)
   {
       if(!strcmp(AFD[l].opname, file) && AFD[l].flag)
       {
        if(AFD[l].opfprotect[0])
        {
            printf("the file has read.\n");
            return ;
        }
        else 
        {
            printf("cannot read!\n");
            return ;
        }
    }
}
if(l>=5)
{
    printf("The file is not open yet. Please open the file first.\n");
    return;
}
}

void Write()
{
   int l;
   char file[10];
   printf("Please enter file name :");
   scanf("%s", file);
   for (l=0; l<5; ++l)
   {
       if(!strcmp(AFD[l].opname, file) && AFD[l].flag)
       {
        if(AFD[l].opfprotect[1])
        {
            printf("the file has write.\n");
            return ;
        }
        else 
        {
            printf("cannot write!\n");
            return ;
        }
    }
}
if(l>=5)
{
    printf("The file is not open yet. Please open the file first.\n");
    return;
}
}

void printUFD(int i)
{
    int k;
    printf("user name\tfile name\tRead Write Execute\t length\n");
    for (k=0; k<10; ++k)
    {
        if (UFD[i].Udir[k].flag)
        {
            printf("%s  \t\t%s\t\t  %d   %d    %d\t\t%dB\n", UFD[i].uname, UFD[i].Udir[k].fname, 
                UFD[i].Udir[k].fprotect[0], UFD[i].Udir[k].fprotect[1], UFD[i].Udir[k].fprotect[2], UFD[i].Udir[k].flength);
        }
    }
}

void printAFD(int i) 
{
   int l, k;
   if (!AFD[0].flag && !AFD[1].flag && !AFD[2].flag && !AFD[3].flag && !AFD[4].flag)
   {
       printf("Currently no open files!\n");
       return ;
   }
   else 
   {
    printf("Open file directory:\n");
    printf("file name\tRead Write Execute\n");
    for (l=0; l<5;++l){
        for (k=0; k<10; ++k)
        {
            if (!strcmp(UFD[i].Udir[k].fname, AFD[l].opname) && UFD[i].Udir[k].flag && AFD[l].flag)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        if (!strcmp(UFD[i].Udir[k].fname, AFD[l].opname) && UFD[i].Udir[k].flag && AFD[l].flag)
        {
            printf("%s\t%d    %d    %d\n", AFD[l].opname, AFD[l].opfprotect[0], AFD[l].opfprotect[1], AFD[l].opfprotect[2]);
        }
    }
}
}

void Close()
{
   int l;
   char file[10];
   printf("Please select file :");
   scanf("%s", file);
   for (l=0; l<5; ++l)
   {
       if (!strcmp(AFD[l].opname, file) && AFD[l].flag)
       {
           AFD[l].flag=0;
           printf("the file has close\n");
           return ;
       }
   }
   if(l>=5) printf("Close file fail!\n");
   return ;
}

void PrintUser()
{
   int i;
   for (i=0; i<10; ++i)
   {
       printf("%s\n", UFD[i].uname);
   }
}

int main()
{
   int i;
   int n=0;
   char m[10];
   char login[10];
   intFSystem();
   printf("Welcome\n");
   printf("This system simulation file management\n");
   printf("The system has initialized 10 users, each user has assigned 5 files\n");
   printf("User's names \n");
   PrintUser();
   printf("**This system contains the following commands\n");
   printf("**Create file(create)\n");
   printf("**Delete file(delete)\n");
   printf("**Open file(open)\n");
   printf("**Close file(close)\n");
   printf("**Read file(read)\n");
   printf("**Write file(write)\n");
   printf("**Show file directory(printufd)\n");
   printf("**Show opened file directory(dir)\n");
   printf("**Exit(exit)");

   lgin:printf("Please enter user name:");
   scanf("%s", login);
   if (!strcmp(login, "exit"))
   {
       return 0;
   }
   for(i=0; i<10; ++i)
   {
       if(!strcmp(UFD[i].uname, login))
        break;
}
if (i>=10) 
{
   printf("This user does not exist\n");
   goto lgin;
}
printUFD(i);
for (;n!=1;){
    printf("Please enter command:");
    scanf("%s", m);
    if (strcmp(m, "create")==0) Create(i);
    else if (strcmp(m, "delete")==0) Delete(i);
    else if (strcmp(m, "open")==0) Open(i);
    else if (strcmp(m, "close")==0) Close();
    else if (strcmp(m, "read")==0) Read();
    else if (strcmp(m, "write")==0) Write();
    else if (strcmp(m, "printufd")==0) printUFD(i);
    else if (strcmp(m, "dir")==0) printAFD(i);
    else if (strcmp(m, "exit")==0) n=1;
    else printf("error\n");
}
printf("Saving...\n");
printUFD(i);
return 0;
}
