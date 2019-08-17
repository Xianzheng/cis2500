#include<stdlib.h>
#include<string.h>
void setStringArray(char **array, int index, char *string)
{
  char *nstring=(char *)malloc((strlen(string)+1)*sizeof(char));
  strcpy(nstring,string);
  array[index]=nstring;
}
