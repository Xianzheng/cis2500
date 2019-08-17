#include <stdlib.h>

char **createStringArray(int number)
{
  int i=0;
  char **Array=(char **)malloc(number *sizeof(char *));
  for(i=0;i<number;i++)
  Array[i]=(char *)malloc(100*sizeof(char));
  return Array;
}
