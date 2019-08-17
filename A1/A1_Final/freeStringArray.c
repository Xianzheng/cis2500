#include<stdlib.h>
void freeStringArray(char **array, int number)
{
  free(array[number]);
  free(array);
}
