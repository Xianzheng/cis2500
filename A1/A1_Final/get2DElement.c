#include <stdio.h>
int get2DElement(int *array, int row, int col)
{
  static int count=0;
  if(row==0)
  {
    count++;
    return *(array+(row+col));
  } else {
  return *(array+(row*count)+col);
  }
}
