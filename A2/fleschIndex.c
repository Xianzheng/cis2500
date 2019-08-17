#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *getfile(char *filename)//function to get all input
{
  FILE *fp;
  int size;
  char *str;
  char ch[1000];
  while((fp=fopen(filename,"r"))==NULL)
  {
    printf("The program was terminated because of open error\n");
    exit(0);
  }
  fseek(fp,0,SEEK_END);
  size=ftell(fp);
  str=(char *)malloc(size);
  str[0]=0;
  rewind(fp);
  while(fgets(ch,1000,fp)!=NULL)
  {
    strcat(str,ch);
  }
  fclose(fp);
  return str;
}

int getSize(char *filename)//function to get file size
{
  int filesize;
  FILE *fp;
  while((fp=fopen(filename,"r"))==NULL)
  {
    printf("The program was terminated because of open error\n");
    exit(0);
  }
  fseek(fp,0,SEEK_END);
  filesize=ftell(fp);
  return filesize;
  printf("%d\n",filesize);
  fclose(fp);
}

int getSyllable(char ch)
{
  if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||ch=='y')
  return 1;
  if(ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U'||ch=='Y')
  return 1;
  if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4')
  return 1;
  if(ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
  return 1;
  if(ch==' '||ch=='\n'||ch=='\0'||ch=='.'||ch=='!')
  return 2;
  if(ch==','||ch==';'||ch=='"'||ch==':'||ch=='?')
  return 2;
  if((ch>'a'&&ch<='z')||(ch>'A'&&ch<='Z'))
  {
    if(ch!='a'||ch!='e'||ch!='i'||ch!='o'||ch!='u'||ch!='y')
    return 0;
    if(ch!='A'||ch!='E'||ch!='I'||ch!='O'||ch!='U'||ch!='Y')
    return 0;
  }
  else return 3;
}

int getEnd(char ch)
{
  if(ch=='a'||ch=='i'||ch=='o'||ch=='u'||ch=='y')
  return 1;
  if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4')
  return 1;
  if(ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
  return 1;
  if(ch=='e')
  return 0;
}

int getWords(char ch)
{
    static int state=0;
    static int words=0;
    if(ch==' '||ch=='\t'||ch=='\n'||ch=='\0')
    {
      state=0;
    }else if(state==0)
    {
      state=1;
      words++;
    }
    return words;
}

int getState(char ch)
{
  static int state=0;

  if(getSyllable(ch)==2)//only of space and end sign state is 0
  {
    state=0;
  }
  else if(state==0)//normal characters state is 2
  {
    state=1;
  }
  return state;
}

int getSentences(char ch)
{
  if(ch=='.'||ch=='!'||ch=='?'||ch==';')
  return 1;
  else return 0;
}

float getIndex(int sy, int words, int se)
{
  float index=0.0;
  if(words>0&&se>0)
  {
  index=206.835-84.6*(sy/words)-1.015*(words/se);
  return index;
  }
  else return 0;
}

int main(int argc, char *argv[])
{
  int i=0,size=0,state;
  int syllables=0,words=0,sentences=0,count=0,counter=0;
  float index=0.0;
  char *str;
  char *filename="myEssay.txt";
  str=getfile(argv[1]);
  size=getSize(argv[1])+1;
  //printf("%s",str);
  for(i=0;i<size;i++)
  {
    if(getState(str[i])==1)
    {
      counter++;
      if(getSyllable(str[i])==1)
      {
        count++;
      }
    }
    //printf("%d",getState(str[i]));
    if(getState(str[i])==0)
    {
      if(getSyllable(str[i-1])!=2)//****#  #is str[i]
      {
        if(count==0)
        {
          if(getSyllable(str[i-1])!=3)// str[i-1]is unknow sign
          {
           syllables++;
          }
        }
      //  printf("fsdc vs<%d\n",count);
        if(count==1&&getEnd(str[i-1])==0)//getEnd(str[i-1]) means 'e'
        {
         syllables++;
         //printf("I am here");
        }
        if(count>1&&getEnd(str[i-1])==0&&getSyllable(str[i-2])==1)
        {//i ncase of tee
          syllables++;
        }
        count=0;
        counter=0;
      }
   }
   if(getSyllable(str[i])==1)//check if it is syllabels
   {
     syllables++;
     if(getSyllable(str[i])==1&&(getSyllable(str[i+1]))==3)
     {
       //syllables--;// in case of nood

     }
     if(getSyllable(str[i])==1&&(getSyllable(str[i+1]))==1)
     {
       syllables--;//tr[i]is syllables and next is a syllable
     }
     if(i>0)
     {
       if(getSyllable(str[i-1])==1&&getSyllable(str[i])==1&&(getSyllable(str[i+1]))==2)
       {
         syllables--; // ee
       }
       if(getSyllable(str[i-1])==0&&getSyllable(str[i])==1&&(getSyllable(str[i+1]))==2)
       {
         syllables--;//pe
       }
     }
     if(getSyllable(str[i-1])!=2&&getEnd(str[i])==1&&getSyllable(str[i+1])==2)
     {
       syllables++;
     }
   }
   if(getSentences(str[i])==1)
   {
     sentences++;
     if(getSentences(str[i])==getSentences(str[i+1]))
     sentences--;
   }
    words=getWords(str[i]);
  }
  index=getIndex(syllables,words,sentences);
  index=index+0.5;

  printf("Flesch Index = %.0f\n",index);
  printf("Syllables Count = %d\n",syllables);
  printf("Word Count = %d\n",words);
  printf("Sentences Count = %d\n",sentences);
  return 0;
}
