#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct contact
{
  unsigned long phone_number;
  long first_name_posn;
  long last_name_posn;
  long company_name_posn;
  long email_posn;
  long next;
};

struct temp
{
  unsigned long phone_number1;
  long first_name_posn1;
  long last_name_posn1;
  long company_name_posn1;
  long email_posn1;
  long next1;
};

struct buf
{
    char firstName[100];
    char lastName[100];
    char companyName[100];
};

struct bu
{
    char lastName[100];
    char companyName[100];
};

typedef struct contact contacts;
typedef struct temp *temper;
typedef struct buf *buffer;
typedef struct bu *b;
int compare_name_ascending(const void *a, const void *b)
{
    const struct buf *ia = (struct buf *)a;
    const struct buf *ib = (struct buf *)b;
    int c = 0;

    c = strcmp(ia->lastName, ib->lastName);

    if (c > 0)
    {
        return c;
    }
    return 0;
}

int getChar(char c)
{
  if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
  return 0;
  else return 1;
}

int getNum(char *p)
{
  int i=0, z=0, count=0;
  while(p[i]!='\0')
  {
    i++;
  }
  for(z=0;z<i;z++)
  {
    if(getChar(p[z])==1)
    count++;
  }
  if(count>0)
  return 0;
  else
  return 1;
}
int checkPhone(char *p)
{
  int i=0, count=0,z=0;
  while(p[i]!='\0')
  {
    i++;
  }
  for(z=0;z<i;z++)
  {
  if(getChar(p[z])==0)
  {
    count++;
  }
  }
  //printf("%d",count);
  if(count==7||count==10)
  return 1;
  else
  return 0;
}

int checkemail(char *email)
{
  char *p;
  p=strstr(email,"@");
  if(!p) return 0;
  if(!(p-email)) return 0;
  if(!(strstr(p,".")-p)) return 0;
  p=strstr(p,".");
  if(*(p+1)=='\0')return 0;
  return 1;
}


void add()
{
  FILE *fp;
  fp = fopen("myContactsList.db","r");
  contacts mycontacts;
  temper tempers;
  int size, i, j, sizeoffile,check=0;
  char *firstName, *lastName, *companyName, *phoneNum, *email;
  char *leftover,action[3];
  unsigned long phone;
  mycontacts.next = 0;
  //tempers = malloc(sizeof(tempers)*1024);
  //ques = malloc(sizeof(char)*1024);
  firstName = malloc(sizeof(char)*1024);
  lastName = malloc(sizeof(char)*1024);
  companyName = malloc(sizeof(char)*1024);
  email = malloc(sizeof(char)*1024);
  phoneNum = malloc(sizeof(char)*50);
  if(fp==NULL)
  {
    fp = fopen("myContactsList.db","w+b");
    sizeoffile=0;
  } else {
    fp = fopen("myContactsList.db","a+b");
    fseek(fp,0,SEEK_END);
    sizeoffile = ftell(fp);
    rewind(fp);
  }

      printf("First Name: ");
      fgets(firstName,50,stdin);
      firstName[strlen(firstName)-1] = '\0';//firstName enter

      printf("Last Name: ");
      fgets(lastName,50,stdin);
      lastName[strlen(lastName)-1] = '\0';//lastName enter

      if(*(lastName+0)=='\0')
      check++;

      printf("Company Name: ");
      fgets(companyName,50,stdin);
      companyName[strlen(companyName)-1] = '\0';//companyName enter

      if(*(companyName+0)=='\0')
      check++;
      while(check==2)
      {
        check=0;
        printf("you must enter either lastName or companyName\n");

          printf("Last Name: ");
          fgets(lastName,50,stdin);
          lastName[strlen(lastName)-1] = '\0';//lastName enter
          if(*(lastName+0)=='\0')
          check++;

          printf("Company Name: ");
          fgets(companyName,50,stdin);
          companyName[strlen(companyName)-1] = '\0';//companyName enter
          if(*(companyName+0)=='\0')
          check++;
      }
      printf("Phone Number(enter only numbers): ");
      fgets(phoneNum,50,stdin);
      phoneNum[strlen(phoneNum)-1] = '\0';
      while(checkPhone(phoneNum)==0||*(phoneNum+0)=='\0'||getNum(phoneNum)==0)
      {
        printf("invalid number, enter only 7 or 10 numbers: ");
        fgets(phoneNum,50,stdin);
        phoneNum[strlen(phoneNum)-1] = '\0';
      }
      phone = strtoul(phoneNum,&leftover,10);
      printf("Email: ");
      fgets(email,50,stdin);
      email[strlen(email)-1] = '\0';//email enter
      while(checkemail(email)==0)
      {
        printf("email is invalid\n");
        printf("Email: ");
        fgets(email,50,stdin);
        email[strlen(email)-1] = '\0';//email enter

      }
      //printf("\n");
      mycontacts.phone_number = phone;

      mycontacts.next = sizeoffile;

      mycontacts.first_name_posn = sizeof(mycontacts) + mycontacts.next;
      //printf("mycontacts.first_name_posn=%llu\n",mycontacts.first_name_posn);
      if(*(firstName+0)!='\0') {
      mycontacts.last_name_posn = mycontacts.first_name_posn + strlen(firstName);
      } else {
      mycontacts.last_name_posn = mycontacts.first_name_posn+ strlen(firstName)+1;
      }
      //printf("mycontacts.last_name_posn=%llu\n",mycontacts.last_name_posn);


      if(*(lastName+0)!='\0') {
      mycontacts.company_name_posn = mycontacts.last_name_posn + strlen(lastName);
      } else {
      mycontacts.company_name_posn = mycontacts.last_name_posn+ strlen(lastName)+1;
      }
      //printf("mycontacts.company_name_posn=%llu\n",mycontacts.company_name_posn);


      if(*(companyName+0)!='\0') {
      mycontacts.email_posn = mycontacts.company_name_posn + strlen(companyName);
      } else {
      mycontacts.email_posn = mycontacts.company_name_posn+ strlen(companyName)+1;
      }
      //printf("email_posn=%llu\n",mycontacts.email_posn);

      //printf("email_posn=%llu\n",mycontacts.email_posn);


      mycontacts.next = mycontacts.email_posn + strlen(email);
      //printf("mycontacts.next=%llu\n",mycontacts.next);
      sizeoffile = mycontacts.next;

      //fwrite to file
      fwrite(&mycontacts,sizeof(mycontacts),1,fp);
      if(*(firstName+0)!='\0') {
      fwrite(firstName,sizeof(char),strlen(firstName),fp);
      } else {
      fwrite("\0",sizeof(char),1,fp);
      }

      if(*(lastName+0)!='\0') {
      fwrite(lastName,sizeof(char),strlen(lastName),fp);
      } else {
      fwrite("\0",sizeof(char),1,fp);
      }

      if(*(companyName+0)!='\0') {
      fwrite(companyName,sizeof(char),strlen(companyName),fp);
      } else {
      fwrite("\0",sizeof(char),1,fp);
      }

      if(*(email+0)!='\0') {
      fwrite(email,sizeof(char),strlen(email),fp);
      } else {
      fwrite("\0",sizeof(char),1,fp);
      }
      printf("Action: ");
      fgets(action,10,stdin);
      action[strlen(action)-1] = '\0';
      printf("\n");
      if(strcmp(action,"S")==0)
      {
        fflush(fp);
      }
      if(strcmp(action,"R")==0)
      {
        //continue;
      }
      free(firstName);
      free(lastName);
      free(companyName);
      free(phoneNum);
      free(email);
}
long * edit(FILE *fq,long *array)
{

  fq = fopen("myContactsList1.db","r");
  contacts mycontacts;
  temper tempers;
  int size, i, j, sizeoffile,check=0;
  char *firstName, *lastName, *companyName, *phoneNum, *email;
  char *leftover;
  unsigned long phone;
  mycontacts.next = 0;
  //tempers = malloc(sizeof(tempers)*1024);
  //ques = malloc(sizeof(char)*1024);
  firstName = malloc(sizeof(char)*1024);
  lastName = malloc(sizeof(char)*1024);
  companyName = malloc(sizeof(char)*1024);
  email = malloc(sizeof(char)*1024);
  phoneNum = malloc(sizeof(char)*50);
  if(fq==NULL)
  {
    fq = fopen("myContactsList1.db","w+b");
    sizeoffile=0;
  } else {
    fq = fopen("myContactsList1.db","a+b");
    fseek(fq,0,SEEK_END);
    sizeoffile = ftell(fq);
    rewind(fq);
  }

  printf("First Name: ");
  fgets(firstName,50,stdin);
  firstName[strlen(firstName)-1] = '\0';//firstName enter

  printf("Last Name: ");
  fgets(lastName,50,stdin);
  lastName[strlen(lastName)-1] = '\0';//lastName enter

  if(*(lastName+0)=='\0')
  check++;

  printf("Company Name: ");
  fgets(companyName,50,stdin);
  companyName[strlen(companyName)-1] = '\0';//companyName enter

  if(*(companyName+0)=='\0')
  check++;
  while(check==2)
  {
    check=0;
    printf("you must enter either lastName of companyName\n");

      printf("Last Name: ");
      fgets(lastName,50,stdin);
      lastName[strlen(lastName)-1] = '\0';//lastName enter
      if(*(lastName+0)=='\0')
      check++;

      printf("Company Name: ");
      fgets(companyName,50,stdin);
      companyName[strlen(companyName)-1] = '\0';//companyName enter
      if(*(companyName+0)=='\0')
      check++;
  }
      printf("Phone Number(enter only numbers): ");
      fgets(phoneNum,50,stdin);
      phoneNum[strlen(phoneNum)-1] = '\0';
      while(checkPhone(phoneNum)==0||*(phoneNum+0)=='\0'||getNum(phoneNum)==0)
      {
        printf("invalid number, enter only 7 or 10 numbers: ");
        fgets(phoneNum,50,stdin);
        phoneNum[strlen(phoneNum)-1] = '\0';
      }

      phone = strtoul(phoneNum,&leftover,10);
      printf("Email: ");
      fgets(email,50,stdin);
      email[strlen(email)-1] = '\0';//email enter
      while(checkemail(email)==0)
      {
        printf("email is invalid\n");
        printf("Email: ");
        fgets(email,50,stdin);
        email[strlen(email)-1] = '\0';//email enter

      }

      mycontacts.phone_number = phone;
      mycontacts.next = sizeoffile;
      mycontacts.first_name_posn = sizeof(mycontacts) + mycontacts.next;
      if(*(firstName+0)!='\0') {
      mycontacts.last_name_posn = mycontacts.first_name_posn + strlen(firstName);
      } else {
      mycontacts.last_name_posn = mycontacts.first_name_posn+ strlen(firstName)+1;
      }

      if(*(lastName+0)!='\0') {
      mycontacts.company_name_posn = mycontacts.last_name_posn + strlen(lastName);
      } else {
      mycontacts.company_name_posn = mycontacts.last_name_posn+ strlen(lastName)+1;
      }
    //  printf("mycontacts.company_name_posn=%llu\n",mycontacts.company_name_posn);


      if(*(companyName+0)!='\0') {
      mycontacts.email_posn = mycontacts.company_name_posn + strlen(companyName);
      } else {
      mycontacts.email_posn = mycontacts.company_name_posn+ strlen(companyName)+1;
      }

    //  printf("email_posn=%llu\n",mycontacts.email_posn);


      mycontacts.next = mycontacts.email_posn + strlen(email);
    //  printf("mycontacts.next=%llu\n",mycontacts.next);
      sizeoffile = mycontacts.next;

      *(array+0)=mycontacts.first_name_posn;
      *(array+1)=mycontacts.last_name_posn;
      *(array+2)=mycontacts.company_name_posn;
      *(array+3)=mycontacts.email_posn;
      *(array+4)=mycontacts.next;

      fwrite(&mycontacts,sizeof(mycontacts),1,fq);
      if(*(firstName+0)!='\0') {
      fwrite(firstName,sizeof(char),strlen(firstName),fq);
      } else {
      fwrite("\0",sizeof(char),1,fq);
      }

      if(*(lastName+0)!='\0') {
      fwrite(lastName,sizeof(char),strlen(lastName),fq);
      } else {
      fwrite("\0",sizeof(char),1,fq);
      }

      if(*(companyName+0)!='\0') {
      fwrite(companyName,sizeof(char),strlen(companyName),fq);
      } else {
      fwrite("\0",sizeof(char),1,fq);
      }

      if(*(email+0)!='\0') {
      fwrite(email,sizeof(char),strlen(email),fq);
      } else {
      fwrite("\0",sizeof(char),1,fq);
      }

      fflush(fq);
      return array;
}

void print(int number,int i, FILE* fp, char *buffer,temper tempers)
{
  fseek(fp,(tempers+i)->first_name_posn1,SEEK_SET);
  fread(buffer,1,(tempers+i)->last_name_posn1-(tempers+i)->first_name_posn1,fp);
  rewind(fp);
  printf("firstName: %s\n",buffer);
  memset(buffer,0,sizeof(buffer));
  fseek(fp,(tempers+i)->last_name_posn1,SEEK_SET);
  fread(buffer,1,(tempers+i)->company_name_posn1-(tempers+i)->last_name_posn1,fp);
  rewind(fp);
  printf("LastName: %s\n",buffer);
  memset(buffer,0,sizeof(buffer));
  fseek(fp,(tempers+i)->company_name_posn1,SEEK_SET);
  fread(buffer,1,(tempers+i)->email_posn1-(tempers+i)->company_name_posn1,fp);
  rewind(fp);
  printf("Company Name: %s\n",buffer);
  memset(buffer,0,sizeof(buffer));
  printf("Phone Number: %ld\n",(tempers+i)->phone_number1);
  memset(buffer,0,sizeof(buffer));
  fseek(fp,(tempers+i)->email_posn1,SEEK_SET);
  fread(buffer,1,(tempers+i)->next1-(tempers+i)->email_posn1,fp);
  rewind(fp);
  printf("Email: %s\n",buffer);
  memset(buffer,0,sizeof(buffer));
  printf("\n");
}

void getAction(char *action)
{
  printf("Action: ");
  fgets(action,10,stdin);
  action[strlen(action)-1] = '\0';
  printf("\n");
}

void copyTemp(FILE *fp, temper tempers, buffer buffers, int i)
{
  memset((buffers+i)->firstName,0,sizeof((buffers+i)->firstName));
  memset((buffers+i)->lastName,0,sizeof((buffers+i)->lastName));
  memset((buffers+i)->companyName,0,sizeof((buffers+i)->companyName));
  fseek(fp,(tempers+i)->first_name_posn1,SEEK_SET);
  fread((buffers+i)->firstName,(tempers+i)->last_name_posn1-(tempers+i)->first_name_posn1,1,fp);
  rewind(fp);
  fseek(fp,(tempers+i)->last_name_posn1,SEEK_SET);
  fread((buffers+i)->lastName,(tempers+i)->company_name_posn1-(tempers+i)->last_name_posn1,1,fp);
  rewind(fp);
  fseek(fp,(tempers+i)->company_name_posn1,SEEK_SET);
  fread((buffers+i)->companyName,(tempers+i)->email_posn1-(tempers+i)->company_name_posn1,1,fp);
  rewind(fp);
}

int getItemNum(FILE *fp,temper tempers,contacts mycontacts, int sizeoffile)
{
  if(sizeoffile==0)
  return 0;
  //printf("%d\n",sizeoffile);
  int z=0;
  while(1)  {
  fread((tempers+z),sizeof(mycontacts),1,fp);
  fseek(fp,(tempers+z)->next1,SEEK_SET);
  //printf("%llu\n",(tempers+z)->next1);
  if((tempers+z)->next1==sizeoffile)
  {
    break;
  }
  if(z>5)
  {
    break;
  }
  z++;//get how many contacts are
  }
  return z;
}
//------------------------------------------------
int main()
{

    contacts mycontacts;
    temper tempers;
    buffer buffers;
    b bbb;
    char action[3];
    char *bu,*buffer;
    FILE *fp;
    int sizeoffile,z=0,i=0,c=0,j=0,number=0,git,size=0,x=0,count=0;

    int (*compare_ptr)(const void *a, const void *b);
    fp = fopen("myContactsList.db","r");
    mycontacts.next = 0;

    tempers = malloc(sizeof(tempers)*200);
    buffers = malloc(sizeof(char)*1024);
    buffer = malloc(sizeof(char)*1024);
    bbb = malloc(sizeof(char)*1024);
    bu = malloc(sizeof(char)*1024);
  //  action = malloc(sizeof(char)*1024);


  //-----------------------------------------------------
    while(strcmp(action,"X")!=0)
    {
      fp = fopen("myContactsList.db","a+b");
      z=0; sizeoffile=0;
      fseek(fp,0,SEEK_END);
      sizeoffile = ftell(fp);
      rewind(fp);
      //memset(tempers,0,sizeof(tempers));
      //get tempers struct from mycontacts
      //printf("%d\n",sizeoffile);
    //  memset(tempers,0,sizeof(tempers));
      z = getItemNum(fp, tempers, mycontacts, sizeoffile);
    //  memset(buffers->firstName,0,sizeof(buffers->firstName));
    //  memset(buffers->lastName,0,sizeof(buffers->lastName));
    //  printf("%d\n",z);
      for(i=0;i<=z;i++)
      {
        copyTemp(fp,tempers,buffers,i);
      }
    //  printf("%d\n",z);
      for(i=0;i<=z;i++)
      {
        if(*((buffers+i)->lastName+0)=='\0')
        {
          fseek(fp,(tempers+i)->company_name_posn1,SEEK_SET);
          fread((buffers+i)->lastName,(tempers+i)->email_posn1-(tempers+i)->company_name_posn1,1,fp);
        }
      }
      //printf("%s\n",(buffers+1)->lastName);
      compare_ptr = &compare_name_ascending;
      qsort ( buffers, z+1, sizeof(struct buf), compare_ptr);
      //printf("\n");
      if(*((buffers+0)->firstName+0)=='\0'&&*((buffers+0)->lastName+0)=='\0'&&*((buffers+0)->companyName+0)=='\0') x=0;
      if(*((buffers+0)->firstName+0)!='\0') x=z+1;

      printf("Number of Contacts=%d\n",x);
      count=0;
      for(c=j;c<=z;c++) {
        count++;
        if(count==6) break;
        if(*((buffers+c)->firstName+0)!='\0') {
           printf("  %d %s %-10s \n",c, (buffers+c)->firstName, (buffers+c)->lastName);
         } else {
           printf("  %d %-10s \n",c,  (buffers+c)->lastName);
        }
      }

      getAction(action);

      if(strcmp(action,"+")==0) {
        j++;
        z++;
      }
      if(strcmp(action,"-")==0) {
        if(j>0&z>0) {
        j--;
        z--;
        }
      }
      if(getNum(action)==1)
      {
        number=atoi(action);
        int r=0,ret=0,check=0;
        long *position, *array;
        int s,cs;
        char old[]="myContactsList.db";
        array=malloc(sizeof(long)*6);
        position=malloc(sizeof(long)*6);

        for(i=0;i<=z;i++)
        {
        fseek(fp,(tempers+i)->last_name_posn1,SEEK_SET);
        fread((bbb+i)->lastName,(tempers+i)->company_name_posn1-(tempers+i)->last_name_posn1,1,fp);
        rewind(fp);
        fseek(fp,(tempers+i)->company_name_posn1,SEEK_SET);
        fread((bbb+i)->companyName,(tempers+i)->email_posn1-(tempers+i)->company_name_posn1,1,fp);
        rewind(fp);
        }
        for(i=0;i<=z;i++)
        {
          //printf("%d",i);

          if(number>z)
          break;
          //printf("(buffers+number)->lastName=%s\n",(buffers+number)->lastName);
          //printf("(bbb+i)->lastName=%s\n",(bbb+i)->lastName);
          //printf("(bbb+i)->companyName=%s\n",(bbb+i)->companyName);
          if(strcmp((buffers+number)->lastName,(bbb+i)->lastName)==0)
          {
            //printf("(buffers+number)->lastName=%s\n",(buffers+number)->lastName);
            //printf("(bbb+i)->lastName=%s\n",(bbb+i)->lastName);
            //printf("1");
            print(number,i,fp,buffer, tempers);
            git=i;
          }
          if(strcmp((buffers+number)->lastName,(bbb+i)->companyName)==0)
          {
            //printf("2");
            print(number,i,fp,buffer, tempers);
            git=i;
          }
        }
        size=(tempers+git)->next1-(tempers+git)->first_name_posn1+48;

        getAction(action);

        if(strcmp(action,"E")==0)
        {
          FILE *fq;
          fq = fopen("myContactsList1.db","w+b");
          fq = fopen("myContactsList1.db","a+b");
          int check=0;
          rewind(fp);


          while(1)
          {
            if(git==z)
            {
              check++;
              if(r==0)
              {
                fseek(fp,0 ,SEEK_SET);
              } else {
                fseek(fp,(tempers+r-1)->next1,SEEK_SET);
              }
              if(r!=git) {
              fread((tempers+r),sizeof(mycontacts),1,fp);
              rewind(fp);
              fseek(fp,(tempers+r)->first_name_posn1,SEEK_SET);
              fread(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fp);
              rewind(fp);
              }

              if(r==0)
              {
                fseek(fq,0 ,SEEK_SET);
              } else {
                fseek(fq,(tempers+r-1)->next1,SEEK_SET);
              }
              if(r!=git) {
                fwrite((tempers+r),sizeof(mycontacts),1,fq);
                rewind(fq);
                fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                rewind(fq);
                memset(buffer,0,sizeof(buffer));
              } else {
                edit(fq,array);
              }
             }
            if(check!=1) {
            if(git==0)
            {

              if(r==0)
              {
              position=edit(fq,array);
              s=48+(*(position+4)-*(position+0));
              cs=size-s;

              }

              if(r==0)
              {
                fseek(fp,size ,SEEK_SET);
              } else {
                fseek(fp,(tempers+r)->next1,SEEK_SET);
              }
              if(r!=git) {

                (tempers+r)->first_name_posn1=(tempers+r)->first_name_posn1-cs;
                (tempers+r)->last_name_posn1=(tempers+r)->last_name_posn1-cs;
                (tempers+r)->company_name_posn1=(tempers+r)->company_name_posn1-cs;
                (tempers+r)->email_posn1=(tempers+r)->email_posn1-cs;
                (tempers+r)->next1=(tempers+r)->next1-cs;

                rewind(fp);
                fseek(fp,(tempers+r)->first_name_posn1+cs,SEEK_SET);
                fread(buffer,(tempers+r)->next1+cs-(tempers+r)->first_name_posn1+cs,1,fp);
                rewind(fp);
              }
              if(r==1)
              {
                fseek(fq,48,SEEK_SET);
              } else {
                fseek(fq,(tempers+r)->next1,SEEK_SET);
              }
              if(r!=git) {
                fwrite((tempers+r),sizeof(mycontacts),1,fq);
                rewind(fq);
                fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                rewind(fq);
                memset(buffer,0,sizeof(buffer));
              }

            }
            }
            if(git!=0&&git!=z)
            {

              if(r<git)
              {
                if(r==0)
                {
                  fseek(fp,0 ,SEEK_SET);
                } else {
                  fseek(fp,(tempers+r-1)->next1,SEEK_SET);
                }
              }
              if(r==git)
              {
                position=edit(fq,array);
                s=48+(*(position+4)-*(position+0));
                cs=size-s;

              }

              if(r>git)
              {
                  fseek(fp,(tempers+r)->next1-cs ,SEEK_SET);
              }
              if(r!=git) {
                if(r<git) {
                  fread((tempers+r),sizeof(mycontacts),1,fp);
                  rewind(fp);
                }
                if(r>git) {
                (tempers+r)->first_name_posn1=(tempers+r)->first_name_posn1-cs;
                (tempers+r)->last_name_posn1=(tempers+r)->last_name_posn1-cs;
                (tempers+r)->company_name_posn1=(tempers+r)->company_name_posn1-cs;
                (tempers+r)->email_posn1=(tempers+r)->email_posn1-cs;
                (tempers+r)->next1=(tempers+r)->next1-cs;
                }

                rewind(fp);
                if(r<git)
                {
                fseek(fp,(tempers+r)->first_name_posn1,SEEK_SET);
                fread(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fp);
                rewind(fp);
                }
                if(r>git)
                {
                  fseek(fp,(tempers+r)->first_name_posn1+cs,SEEK_SET);
                  fread(buffer,(tempers+r)->next1+cs-(tempers+r)->first_name_posn1+cs,1,fp);
                }

                rewind(fp);
              }
              if(r<git)
              {
                if(r==0)
                {
                  fseek(fq,0 ,SEEK_SET);
                } else {
                  fseek(fq,(tempers+r-1)->next1,SEEK_SET);
                }
                if(r!=git) {
                  fwrite((tempers+r),sizeof(mycontacts),1,fq);
                  rewind(fq);
                  fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                  fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                  rewind(fq);
                  memset(buffer,0,sizeof(buffer));
                }
              }

              if(r>git)
              {

                fseek(fp,(tempers+r)->next1-cs ,SEEK_SET);


              if(r!=git) {
                fwrite((tempers+r),sizeof(mycontacts),1,fq);
                rewind(fq);
                fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                rewind(fq);
                memset(buffer,0,sizeof(buffer));
              }
             }

            }
            if(r==z)
            break;
            r++;
          }

          remove(old);
          rename("myContactsList1.db","myContactsList.db");
          free(fq);
          continue;
        }

//---------------------------------------------------
        if(strcmp(action,"D")==0)
        {

           FILE *fq;
           fq = fopen("myContactsList1.db","w+b");
           fq = fopen("myContactsList1.db","a+b");
           rewind(fp);

           while(1)
           {
             if(git==z)
             {
               size=0;
               if(r==0)
               {
                 fseek(fp,0 ,SEEK_SET);
               } else {
                 fseek(fp,(tempers+r-1)->next1,SEEK_SET);
               }
               if(r!=git) {
                 fread((tempers+r),sizeof(mycontacts),1,fp);
                 rewind(fp);
                 fseek(fp,(tempers+r)->first_name_posn1,SEEK_SET);
                 fread(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fp);
                 rewind(fp);
               }


               if(r==0)
               {
                 fseek(fq,0 ,SEEK_SET);
               } else {
                 fseek(fq,(tempers+r-1)->next1,SEEK_SET);
               }
               if(r!=git) {
                 fwrite((tempers+r),sizeof(mycontacts),1,fq);
                 rewind(fq);
                 fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                 fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                 rewind(fq);
                 memset(buffer,0,sizeof(buffer));
               }


           }
//---------------------------------------------------------
            if(git==0)
            {
              if(r==0)
              {
                fseek(fp,size ,SEEK_SET);
              } else {
                fseek(fp,(tempers+r)->next1,SEEK_SET);
              }
              if(r!=git) {

                (tempers+r)->first_name_posn1=(tempers+r)->first_name_posn1-size;
                (tempers+r)->last_name_posn1=(tempers+r)->last_name_posn1-size;
                (tempers+r)->company_name_posn1=(tempers+r)->company_name_posn1-size;
                (tempers+r)->email_posn1=(tempers+r)->email_posn1-size;
                (tempers+r)->next1=(tempers+r)->next1-size;

                rewind(fp);
                fseek(fp,(tempers+r)->first_name_posn1+size,SEEK_SET);
                fread(buffer,(tempers+r)->next1+size-(tempers+r)->first_name_posn1+size,1,fp);
                rewind(fp);
              }
              if(r==1)
              {
                fseek(fq,0 ,SEEK_SET);
              } else {
                fseek(fq,(tempers+r)->next1,SEEK_SET);
              }
              if(r!=git) {
                fwrite((tempers+r),sizeof(mycontacts),1,fq);
                rewind(fq);
                fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                rewind(fq);
                memset(buffer,0,sizeof(buffer));
              }

            }
//=========--------------------------------------------------------------------
            if(git!=0&&git!=z)
            {

              if(r<git)
              {
                if(r==0)
                {
                  fseek(fp,0 ,SEEK_SET);
                } else {
                  fseek(fp,(tempers+r-1)->next1,SEEK_SET);
                }
              }

              if(r>git)
              {
                  fseek(fp,(tempers+r)->next1-size ,SEEK_SET);
              }
              if(r!=git) {
                if(r<git) {
                  fread((tempers+r),sizeof(mycontacts),1,fp);
                  rewind(fp);
                }
                if(r>git) {
                (tempers+r)->first_name_posn1=(tempers+r)->first_name_posn1-size;
                (tempers+r)->last_name_posn1=(tempers+r)->last_name_posn1-size;
                (tempers+r)->company_name_posn1=(tempers+r)->company_name_posn1-size;
                (tempers+r)->email_posn1=(tempers+r)->email_posn1-size;
                (tempers+r)->next1=(tempers+r)->next1-size;
                }

                rewind(fp);
                if(r<git)
                {
                fseek(fp,(tempers+r)->first_name_posn1,SEEK_SET);
                fread(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fp);
                rewind(fp);
                }
                if(r>git)
                {
                  fseek(fp,(tempers+r)->first_name_posn1+size,SEEK_SET);
                  fread(buffer,(tempers+r)->next1+size-(tempers+r)->first_name_posn1+size,1,fp);
                }
                rewind(fp);
              }
              if(r<git)
              {
                if(r==0)
                {
                  fseek(fq,0 ,SEEK_SET);
                } else {
                  fseek(fq,(tempers+r-1)->next1,SEEK_SET);
                }
                if(r!=git) {
                  fwrite((tempers+r),sizeof(mycontacts),1,fq);
                  rewind(fq);
                  fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                  fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                  rewind(fq);
                  memset(buffer,0,sizeof(buffer));
                }
              }

              if(r>git)
              {
                fseek(fp,(tempers+r)->next1-size ,SEEK_SET);
              if(r!=git) {
                fwrite((tempers+r),sizeof(mycontacts),1,fq);
                rewind(fq);
                fseek(fq,(tempers+r)->first_name_posn1,SEEK_SET);
                fwrite(buffer,(tempers+r)->next1-(tempers+r)->first_name_posn1,1,fq);
                rewind(fq);
                memset(buffer,0,sizeof(buffer));
              }
             }

            }
            if(r==z)
            break;
            r++;

           }

          remove(old);
          rename("myContactsList1.db","myContactsList.db");
           continue;

        }

        if(strcmp(action,"R")==0)
        {
          continue;
        }
      }
      if(strcmp(action,"A")==0)
      {
        add();
      }
    }
    free(tempers);
    free(buffers);
    free(buffer);
    free(bbb);
    free(bu);
    fclose(fp);
    //fclose(fq);
    return 0;

}
