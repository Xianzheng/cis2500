#ifndef HEADER_FILE
#define HEADER_FILE


int *create2DArray(int rows, int cols);
char **createStringArray(int number);
int **createArray(int rows, int cols);
void free2DArray(int *array);
void freeArray(int **Array, int rows, int cols);
void freeStringArray(char **array, int number);
int get2DElement(int *array, int row, int col);
char *getStringArray(char **array, int index);
void set2DElement(int *array, int row, int col, int value);
void setStringArray(char **array, int index, char *string);


#endif
