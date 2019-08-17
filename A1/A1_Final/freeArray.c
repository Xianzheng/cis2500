#include<stdlib.h>
void freeArray(int **Array, int rows, int cols)
{
  free(Array[rows]);
  free(Array);
}
