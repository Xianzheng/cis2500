#include <stdlib.h>
int *create2DArray(int rows, int cols)
{
  int *Array=(int *)malloc(sizeof(int)*rows*cols);
  int i=0;
  for( i=0; i<rows*cols; i++)
  {
    Array[i]=0;
  }
  return Array;
}
