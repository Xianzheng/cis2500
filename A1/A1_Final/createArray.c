#include<stdlib.h>
int **createArray(int rows, int cols)
{

  int **iptr=(int **)malloc(sizeof(int *)*rows);
  int i,j;
  for(i=0;i<rows;i++) {
    iptr[i]=(int *)malloc(sizeof(int)*rows);
  }
  for(i=0;i<rows;i++) {
    for(j=0;j<cols;j++) {
      iptr[i][j]=0;
    }
  }
  return iptr;
}
