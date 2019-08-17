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

typedef struct contact contacts;
typedef struct temp *temper;
int getChar(char c)
{
  if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
  return 0;
  else return 1;
}
int check(char *p)
{
  //printf("%c",p[0]);
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
  return 1;
  else return 0;

}
int main()
{
  FILE *fp;
  fp = fopen("myContactsList.db","r");
  contacts mycontacts;
  temper tempers;
  int size, i, j, sizeoffile;
  char *firstName, *lastName, *companyName, *phoneNum, *email;
  char *ques,  *buffer, *leftover;
  unsigned long phone;
  mycontacts.next = 0;
  tempers = malloc(sizeof(tempers)*1024);
  ques = malloc(sizeof(char)*1024);
  firstName = malloc(sizeof(char)*1024);
  lastName = malloc(sizeof(char)*1024);
  companyName = malloc(sizeof(char)*1024);
  email = malloc(sizeof(char)*1024);
  phoneNum = malloc(sizeof(char)*50);
  buffer = malloc(sizeof(char)*1024);
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

  while(1)
  {
    printf("Do you wish to enter a new contact(Yes or No)?: ");
    fgets(ques,50,stdin);
    ques[strlen(ques)-1] = '\0';
    if(strcmp(ques,"Yes")==0)
    {
      printf("First Name: ");
      fgets(firstName,50,stdin);
      firstName[strlen(firstName)-1] = '\0';//firstName enter
      printf("Last Name: ");
      fgets(lastName,50,stdin);
      lastName[strlen(lastName)-1] = '\0';//lastName enter
      printf("Company Name: ");
      fgets(companyName,50,stdin);
      companyName[strlen(companyName)-1] = '\0';//companyName enter
      printf("Phone Number(enter only numbers): ");
      fgets(phoneNum,50,stdin);
      phoneNum[strlen(phoneNum)-1] = '\0';
      while(*(phoneNum+0)=='\0'||check(phoneNum)==1)
      {
        printf("You typed a invald phone number which must be a number\n");
        printf("Phone Number: ");
        fgets(phoneNum,50,stdin);
        phoneNum[strlen(phoneNum)-1] = '\0';
      }

      phone = strtoul(phoneNum,&leftover,10);
      printf("Email: ");
      fgets(email,50,stdin);
      email[strlen(email)-1] = '\0';//email enter
      mycontacts.phone_number = phone;

      mycontacts.next = sizeoffile;

      if(*(firstName+0)!='\0') {
      mycontacts.first_name_posn = sizeof(mycontacts) + mycontacts.next;
      } else {
      mycontacts.first_name_posn = sizeof(mycontacts)+ mycontacts.next-1;
      }

      if(*(lastName+0)!='\0') {
      mycontacts.last_name_posn = mycontacts.first_name_posn + strlen(firstName)+1;
      } else {
      mycontacts.last_name_posn = mycontacts.first_name_posn+ strlen(firstName);
      }

      if(*(companyName+0)!='\0') {
      mycontacts.company_name_posn = mycontacts.last_name_posn + strlen(lastName)+1;
      } else {
      mycontacts.company_name_posn = mycontacts.last_name_posn+ strlen(lastName);
      }

      if(*(email+0)!='\0') {
      mycontacts.email_posn = mycontacts.company_name_posn + strlen(companyName)+1;
      } else {
      mycontacts.email_posn = mycontacts.company_name_posn+ strlen(lastName);
      }
      mycontacts.next = mycontacts.email_posn + strlen(email)+1;
      sizeoffile = mycontacts.next;

      //fwrite to file
      fwrite(&mycontacts,sizeof(mycontacts),1,fp);
      if(*(firstName+0)!='\0') {
      fwrite(firstName,sizeof(char),strlen(firstName)+1,fp);
      }
      if(*(lastName+0)!='\0') {
      fwrite(lastName,sizeof(char),strlen(lastName)+1,fp);
      }
      if(*(companyName+0)!='\0') {
      fwrite(companyName,sizeof(char),strlen(companyName)+1,fp);
      }
      if(*(email+0)!='\0') {
      fwrite(email,sizeof(char),strlen(email)+1,fp);
      }
      i++;

    }
    if(strcmp(ques,"No")==0)
    {
      printf("Do you wish to retrieve the a contact(Yes or No)? ");
      fgets(ques,50,stdin);
      ques[strlen(ques)-1] = '\0';
      if(strcmp(ques,"Yes")==0)
      {
        int z=0;
        printf("Phone Number(enter only numbers): ");
        fgets(phoneNum,50,stdin);
        phoneNum[strlen(phoneNum)-1] = '\0';
        phone = strtoul(phoneNum,&leftover,10);
        fseek(fp,0,SEEK_END);
        sizeoffile = ftell(fp);
        rewind(fp);
        fp = fopen("myContactsList.db","a+b");

        while(1)
        {
        fread((tempers+z),sizeof(mycontacts),1,fp);
        fseek(fp,(tempers+z)->next1,SEEK_SET);


        if((tempers+z)->phone_number1== phone)
        {

          fseek(fp,(tempers+z)->first_name_posn1,SEEK_SET);
          fread(buffer,1,(tempers+z)->last_name_posn1-(tempers+z)->first_name_posn1,fp);
          rewind(fp);
          printf("firstName: %s\n",buffer);
          memset(buffer,0,sizeof(buffer));
          fseek(fp,(tempers+z)->last_name_posn1,SEEK_SET);
          fread(buffer,1,(tempers+z)->company_name_posn1-(tempers+z)->last_name_posn1,fp);
          rewind(fp);
          printf("LastName: %s\n",buffer);
          memset(buffer,0,sizeof(buffer));
          fseek(fp,(tempers+z)->company_name_posn1,SEEK_SET);
          fread(buffer,1,(tempers+z)->email_posn1-(tempers+z)->company_name_posn1,fp);
          rewind(fp);
          printf("Company Name: %s\n",buffer);
          memset(buffer,0,sizeof(buffer));
          printf("Phone Number: %ld\n",phone);
          memset(buffer,0,sizeof(buffer));
          fseek(fp,(tempers+z)->email_posn1,SEEK_SET);
          fread(buffer,1,(tempers+z)->next1-(tempers+z)->email_posn1,fp);
          rewind(fp);
          printf("Email: %s\n",buffer);
          memset(buffer,0,sizeof(buffer));
          break;
        }

        if((tempers+z)->next1==sizeoffile)
        {
          printf("No match found\n");
          break;
        }
        z++;
        }

      }
      if(strcmp(ques,"No")==0)
      {
        break;
      }
    }
  }
  free(ques);
  free(firstName);
  free(lastName);
  free(companyName);
  free(email);
  free(tempers);
  free(phoneNum);
  free(buffer);
}
