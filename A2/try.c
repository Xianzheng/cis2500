#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *getfile(char *fname)
{
  FILE *fp;
  char *str;
  char txt[1000];
  int filesize;
  if((fp=fopen(fname,"r"))==NULL)
  {
    printf("OPEN ERROR");
    return 0;
  }

  fseek(fp,0,SEEK_END);
  filesize=ftell(fp);
  str=(char *)malloc(filesize);
  str[0]=0;

  rewind(fp);
  while(fgets(txt,1000,fp)!=NULL)
  {
    strcat(str,txt);
  }
  fclose(fp);
  return str;

}

int main()
{
  char *str;
  char *fname;
  fname="text.txt";
  str = getfile(fname);
  printf("%s",str);
  return 0;
}
