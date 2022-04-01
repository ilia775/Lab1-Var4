#ifndef _lablib_h
#define _lablib_h
typedef struct Matrix {
    void** element;
    int y;
    int x;
    int typeofelement;
} matrix;

void menu(int type);
matrix matrixalloc(int vvod, int x, int y);
void freematrix(matrix* mat);
void matrixfromconsole(matrix* mat);
void matrixfromrandom(matrix* mat);
void matrixtoconsole(matrix* mat);
void matrixsum(matrix* mat1, matrix* mat2);
matrix matrixmult(matrix* mat1, matrix mat2);
void matrixcpy(matrix* mat1, matrix* mat2);
matrix matrixtrans(matrix* mat1);
void matrixadd(matrix* mat1);

#endif