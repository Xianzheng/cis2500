void set2DElement(int *array, int row, int col, int value)
{
  int i=0, num=0;
  for(i=0;i<value;i++)
  {
    num++;
    *(array+i)=num;
  }
}
