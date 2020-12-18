#include<stdlib.h>
#include<stdio.h>
#define MAX_TERMS 50

typedef struct{
    int row;
    int col;
    float value;
} matrix_term;

//Create
matrix_term* create_matrix(){
    matrix_term* ptr = (matrix_term*)malloc(sizeof(matrix_term) * MAX_TERMS);
    ptr[0].row = 0;ptr[0].col = 0;ptr[0].value = 0;
    return ptr;
}
void delete_matrix(matrix_term* ptr){
    if (ptr) free(ptr);
}

//Add
matrix_term* add_matrix(matrix_term* matrix1, matrix_term* matrix2){
    matrix_term* result;
    result = create_matrix();

    if ((matrix1[0].row != matrix2[0].row || matrix1[0].col != matrix2[0].col) || !result){
        return NULL;
    }
    else{
        int i = 1, j = 1, k = 1;

        result[0].row = matrix1[0].row;
        result[0].col = matrix1[0].col;

        while (i <= matrix1[0].value && j <= matrix2[0].value){
            if (matrix1[i].row < matrix2[j].row){
                result[k] = matrix1[i];
                i++;
            }
            else if (matrix1[i].row == matrix2[j].row){
                if (matrix1[i].col < matrix2[j].col){
                    result[k] = matrix1[i];
                    i++;
                }
                else if (matrix1[i].col == matrix2[j].col){
                    result[k]=matrix1[i];
                    result[k].value = matrix1[i].value + matrix2[j].value;
                    i++;j++;
                }
                else{
                    result[k] = matrix2[j];
                    j++;
                }
            }
            else{
                result[k] = matrix2[j];
                j++;
            }

            k++;
        }

        while (i <= matrix1[0].value) result[k++] = matrix1[i++];
        while (j <= matrix2[0].value) result[k++] = matrix2[j++];

        result[0].value = k - 1;

    }
}

//Transpose
//fast transpose algorithm is used
matrix_term* transpose(matrix_term* matrix){
    int rowTerms[MAX_TERMS], startingPos[MAX_TERMS];

    for (int i = 0;i < MAX_TERMS;i++) rowTerms[i] = 0;
    for (int i = 1;i <= matrix->value;i++) rowTerms[matrix[i].col]++;

    startingPos[0] = 1;
    for (int i = 1;i <= matrix->col;i++) startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

    matrix_term* transpose_m = create_matrix();
    if (!transpose_m) return NULL;
    transpose_m[0].row = matrix[0].col;
    transpose_m[0].col = matrix[0].row;
    transpose_m[0].value = matrix[0].value;

    for (int i = 1;i <= matrix[0].value;i++){
        int j = startingPos[matrix[i].col]++;
        transpose_m[j].row = matrix[i].col;
        transpose_m[j].col = matrix[i].row;
        transpose_m[j].value = matrix[i].value;
    }

    return transpose_m;
}


//Multiply
matrix_term* multiply_matrix(matrix_term* m1,matrix_term* m2){
    
}

//print
void print_matrix(matrix_term* matrix){
    if (!matrix) return;
    int k = 1;
    for (int r = 1;r <= matrix[0].row;r++){
        for (int c = 1;c <= matrix[0].col;c++){
            if (matrix[k].row == r && matrix[k].col == c){
                printf("%.0f\t", matrix[k].value);
                k++;
            }
            else printf("0\t");
        }
        printf("\n\n");
    }
}
