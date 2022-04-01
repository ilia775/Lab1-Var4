#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lablib.h"

void freematrix(matrix* mat) {
    for (int i = 0; i < mat->y; i++) free(mat->element[i]);
    free(mat->element);
}

matrix matrixalloc(int type, int x, int y) {
    matrix mat;
    mat.x = x;
    mat.y = y;
    if (type == 1) {
        mat.typeofelement = 1;
        mat.element = (int**)malloc(sizeof(int*) * y);
        for (int i = 0; i < y; i++) {
            mat.element[i] = (int*)malloc(sizeof(int) * x);
            for (int j = 0; j < x; j++) ((int**)mat.element)[i][j] = 0;
        }
    }
    if (type == 2) {
        mat.typeofelement = 2;
        mat.element = (double**)malloc(sizeof(double*) * y);
        for (int i = 0; i < y; i++) {
            mat.element[i] = (double*)malloc(sizeof(double) * x);
            for (int j = 0; j < x; j++) ((double**)mat.element)[i][j] = 0;
        }
    }

    return mat;
}

void matrixfromconsole(matrix* mat) {
    //printf("matrixfromconsole start...\n");
    printf("Enter %d rows and %d columns\n", mat->y, mat->x);
    for (int i = 0; i < mat->y; i++) {
        for (int t = 0; t < mat->x; t++) {
            if (mat->typeofelement == 1) {
                int temp = -1;
                scanf("%d", &temp);
                scanf("%*c");
                ((int**)mat->element)[i][t] = temp;

            }
            else {
                double temp = -1;
                scanf("%lf", &temp);
                scanf("%*c");
                ((double**)mat->element)[i][t] = temp;
            }
        }
    }
    //printf("matrixfromconsole end...\n");
}

void matrixfromrandom(matrix* mat) {
    srand(time(NULL));
    //printf("matrixfromrandom start...\n");
    for (int i = 0; i < mat->y; i++) {
        for (int t = 0; t < mat->x; t++) {
            if (mat->typeofelement == 1) {
                ((int**)mat->element)[i][t] = rand() % 10000;
                if (rand() % 2 == 1) ((int**)mat->element)[i][t] *= -1;
            }
            else {
                ((double**)mat->element)[i][t] = (double)(rand()) / (double)(RAND_MAX) * 1000;
                if (rand() % 2 == 1) ((double**)mat->element)[i][t] *= -1;
            }
        }
    }
    //printf("matrixfromrandom end...\n");
}

void matrixtoconsole(matrix* mat) {
    //printf("matrixtoconsole start...\n");
    for (int i = 0; i < mat->y; i++) {
        for (int t = 0; t < mat->x; t++) {
            if (mat->typeofelement == 1) printf("%10d ", ((int**)mat->element)[i][t]);
            else printf("%10.3lf ", ((double**)mat->element)[i][t]);
        }
        printf("\n");
    }
    //printf("matrixtoconsole end...\n");
}

void matrixsum(matrix* mat1, matrix* mat2) {
    if (mat1->typeofelement == 1) for (int i = 0; i < mat1->y; i++) {
        for (int j = 0; j < mat1->x; j++) {
            ((int**)mat1->element)[i][j] += ((int**)mat2->element)[i][j];
        }
    }
    else if (mat1->typeofelement == 2) for (int i = 0; i < mat1->y; i++) {
        for (int j = 0; j < mat1->x; j++) {
            ((double**)mat1->element)[i][j] += ((double**)mat2->element)[i][j];
        }
    }
    /*int type = -1, form = -1;
    if (mat1->typeofelement == 1) type = 1;
    else type = 2;
    matrix mat2 = matrixalloc(type, mat1->x, mat1->y);
    printf("Select input format:\n1. Manual.\n2. Random.\n");
    scanf("%d", &form);
    scanf("%*c");
    if (form == 1) matrixfromconsole(&mat2);
    else if (form == 2) matrixfromrandom(&mat2);
    for (int i = 0; i < mat1->y; i++) {
        for (int t = 0; t < mat1->x; t++) {
            if (type == 1) ((int**)mat1->element)[i][t] += ((int**)mat2.element)[i][t];
            else if (type == 2) ((double**)mat1->element)[i][t] += ((double**)mat2.element)[i][t];
        }
    }
    freematrix(&mat2);*/
}



matrix matrixmult(matrix* mat1, matrix mat2) {
    int type = mat1->typeofelement, form = -1, x = -1;
    //matrixtoconsole(&mat2);
    matrix mat = matrixalloc(type, mat2.x, mat1->y);
    for (int i = 0; i < mat1->y; i++) {
        for (int j = 0; j < mat2.x; j++) {
            if (type == 1) {
                ((int**)mat.element)[i][j] = 0;
                for (int k = 0; k < mat2.y; k++) {
                    ((int**)mat.element)[i][j] += ((int**)mat1->element)[i][k] * ((int**)mat2.element)[k][j];
                }
            }
            else if (type == 2) {
                ((double**)mat.element)[i][j] = 0;
                for (int k = 0; k < mat.x; k++) {
                    ((double**)mat.element)[i][j] += ((double**)mat1->element)[i][k] * ((double**)mat2.element)[k][j];
                }
            }
        }
    }
    freematrix(mat1);
    //freematrix(&mat2);
    return mat;
}

void matrixcpy(matrix* mat1, matrix* mat2) {
    for (int i = 0; i < mat1->y; i++) {
        for (int t = 0; t < mat1->x; t++) {
            if (mat1->typeofelement == 1) ((int**)mat2->element)[i][t] = ((int**)mat1->element)[i][t];
            else ((double**)mat2->element)[i][t] = ((double**)mat1->element)[i][t];
        }
    }
}

matrix matrixtrans(matrix* mat1) {
    int type = -1;
    if (mat1->typeofelement == 1) type = 1;
    else type = 2;
    matrix mat2 = matrixalloc(type, mat1->y, mat1->x);
    for (int i = 0; i < mat1->y; i++) {
        for (int k = 0; k < mat1->x; k++) {
            if (type == 1) {
                ((int**)mat2.element)[k][i] = ((int**)mat1->element)[i][k];
            }
            else if (type == 2) {
                ((double**)mat2.element)[k][i] = ((double**)mat1->element)[i][k];
            }
            /*if (type == 1) {
                int temp = ((int**)mat1->element)[i][k];
                ((int**)mat1->element)[i][k] = ((int**)mat1->element)[k][i];
                ((int**)mat1->element)[k][i] = temp;
            }
            else {
                double temp = ((double**)mat1->element)[i][k];
                ((double**)mat1->element)[i][k] = ((double**)mat1->element)[k][i];
                ((double**)mat1->element)[k][i] = temp;
            }*/
        }
    }
    freematrix(mat1);
    return mat2;
}

void matrixadd(matrix* mat1) {
    int affrow = -5, type = -1, vvod = -2;
    double num = 1;
    matrix LinearCombination = matrixalloc(mat1->typeofelement, mat1->x, 1);
    if (mat1->typeofelement == 1) type = 1;
    else type = 2;
    //matrix mat2 = matrixalloc(type, mat1->x, 1);
    //if (type == 1) for (int i = 0; i < mat2.x; i++) ((int**)mat2.element)[0][i] = 0;
    //else for (int i = 0; i < mat2.x; i++) ((double**)mat2.element)[0][i] = 0;
    while (1) {
        printf("Select affected row:\n");
        scanf("%d", &affrow);
        if (affrow >= 0 && affrow < mat1->y) break;
        printf("incorrect input\n");
    }
    while (1) {
        //printf("sum = {");
        printf("Select row to add to linear combination(-1 to show matrix or -2 to show linear combination or -3 to end this algorithm):\n");
        scanf("%d", &vvod);
        scanf("%*c");
        if (vvod == -1) {
            matrixtoconsole(mat1);
            continue;
        }
        else if (vvod == -2) {
            matrixtoconsole(&LinearCombination);
            continue;
        }
        else if (vvod == -3) break;
        else if (vvod < 0 || vvod >= mat1->y) {
            printf("Incorrect input\n");
            continue;
        }

        printf("Enter number to multiply by this row:\n");
        scanf("%lf", &num);
        scanf("%*c");
        if (LinearCombination.typeofelement == 1) for (int i = 0; i < LinearCombination.x; i++) ((int**)LinearCombination.element)[0][i] += (int)(num) * ((int**)mat1->element)[vvod][i];
        else for (int i = 0; i < LinearCombination.x; i++) ((double**)LinearCombination.element)[0][i] += (double)(num) * ((double**)mat1->element)[vvod][i];

    }
    printf("Enter number to multiply by Linear combination:\n");
    scanf("%lf", &num);
    scanf("%*c");
    if (type == 1) for (int i = 0; i < mat1->x; i++) ((int**)mat1->element)[affrow][i] += (int)num * ((int**)LinearCombination.element)[0][i];
    else for (int i = 0; i < mat1->x; i++) ((double**)mat1->element)[affrow][i] += (double)num * ((double**)LinearCombination.element)[0][i];
    freematrix(&LinearCombination);
}

matrix GetMatrix(int type, int x, int y) {
    matrix mat2 = matrixalloc(type, x, y);
    int form = 0;
    while (1) {
        printf("Select input format:\n1. Manual.\n2. Random.\n");
        scanf("%d", &form);
        scanf("%*c");
        if (form == 1 || form == 2) break;
        printf("Incorrect input\n");
    }
    if (form == 1) matrixfromconsole(&mat2);
    else if (form == 2) matrixfromrandom(&mat2);
    return mat2;
}

void menu(int type) {
    int act = -1;
    matrix mat1;
    mat1.typeofelement = 0;
    while (act != 0) {
        while (1) {
            //printf(" 2 - %d\n", mat1.sizeofelement);
            printf("Choose action:\n1. Input.\n2. Output.\n3. Processing\n0. End programm\n");
            scanf("%d", &act);
            scanf("%*c");
            if (act == 1 || act == 2 || act == 3 || act == 0) break;
            else printf("Incorrect input\n");
        }
        if (act == 1) {
            if (mat1.typeofelement != 0) {
                freematrix(&mat1);
                matrix mat1;
                mat1.typeofelement = 0;
            }
            printf("Enter size of matrix: y and x\n");
            int x = -1, y = -1, form = -1;
            scanf("%d %d", &y, &x);
            mat1 = matrixalloc(type, x, y);
            printf("Select input format:\n1. Manual.\n2. Random.\n");
            scanf("%d", &form);
            scanf("%*c");
            if (form == 1) matrixfromconsole(&mat1);
            else if (form == 2) matrixfromrandom(&mat1);
            else printf("Incorrect input\n");
            //printf(" 0 - %d\n", mat1.sizeofelement);
        }
        if (act == 2) {
            //printf("%d\n", mat1.typeofelement);
            if (mat1.typeofelement != 0) matrixtoconsole(&mat1);
            else printf("Nothing to display\n");
        }
        if (act == 3) {
            if (mat1.typeofelement == 0) {
                printf("Nothing to process\n");
                continue;
            }
            printf("Choose action:\n1. Sum.\n2. Multiplication.\n3. Transposition.\n4. Adding a linear combination to string\n");
            int act1 = -1;
            scanf("%d", &act1);
            scanf("%*c");
            if (act1 == 1) {
                matrix mat2 = GetMatrix(mat1.typeofelement, mat1.x, mat1.y);
                matrixsum(&mat1, &mat2);
                freematrix(&mat2);
            }
            else if (act1 == 2) {
                int x32;
                printf("Select x for second matrix:\n");
                scanf("%d", &x32);
                scanf("%*c");
                matrix mat2 = GetMatrix(mat1.typeofelement, x32, mat1.x);
                mat1 = matrixmult(&mat1, mat2);
                freematrix(&mat2);
            }
            else if (act1 == 3) mat1 = matrixtrans(&mat1);
            else if (act1 == 4) matrixadd(&mat1);
        }
    }
    if (mat1.typeofelement != 0) freematrix(&mat1);
}