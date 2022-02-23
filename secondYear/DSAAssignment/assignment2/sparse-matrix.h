#include<stdlib.h>
#include<stdio.h>
#define MAX_TERMS 50

typedef struct{
    int row;
    int col;
    float value;
} matrix_term;

matrix_term* create_matrix();
void delete_matrix(matrix_term* ptr);
matrix_term* add_matrix(matrix_term* matrix1, matrix_term* matrix2);
matrix_term* transpose(matrix_term* matrix);
matrix_term* multiply_matrix(matrix_term* m1, matrix_term* m2);
void print_matrix(matrix_term* matrix);

//Below Function are for internal use only(FOr this header file)
void storeSum(matrix_term* m, int* totalm, int row, int col, float* sum);
int compare(int n1, int n2);


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
    if(!matrix){
        return NULL;
    }

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
    if(!(m1 && m2) || (m1->col != m2->row)) return NULL;

    matrix_term* result = create_matrix();
    int row,col,rowBeginM1,totalR; //totalR represents number of nonzero value in resulting matrix
    float sum;
    matrix_term* transm = transpose(m2); //Transpose of m2

    //Initialise value for the multiplication loops
    row = m1[1].row;rowBeginM1 = 1;sum=0;totalR=0;
    //Put sentinal in m1 and transm
    m1[(int)(m1->value+1)].row = m1->row;
    transm[(int)(m2->value + 1)].row = m2->col;
    transm[(int)(m2->value + 1)].col = 0;

    //Multiply row of m1 with column of m2(row of transm)
    for(int i=1;i<=m1[0].value;){
        col = transm[1].row;

        for(int j=1;j<=m2[0].value;){
            if(m1[i].row != row){
                storeSum(result,&totalR,row,col,&sum);
                for(;transm[j].row == col;j++);
                col = transm[j].row;i=rowBeginM1;
            }else if(transm[j].row != col){
                storeSum(result,&totalR,row,col,&sum);
                i=rowBeginM1;
                col = transm[j].row;
            }else{
                switch (compare(m1[i].col, transm[j].col)){
                case -1: i++;break;
                case 0:{
                    sum += m1[i].value * transm[j].value;
                    i++;j++;
                };break;
                case 1: j++;break;  
                }
            }
        }
        storeSum(result,&totalR,row,col,&sum);

        for(;m1[i].row == row;i++);
        rowBeginM1 = i;
        row = m1[i].row;
    }

    result[0].row = m1->row;
    result[0].col = m2->col;
    result[0].value = totalR;

    //Free transm before returning
    delete_matrix(transm);

    return result;
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


/* For internal library use only */
void storeSum(matrix_term* m, int* totalm, int row, int col, float* sum){
    if(*sum){
        if(*totalm >= MAX_TERMS-1){
            printf("Boundary crossed!\n");
        }else{
            m[++(*totalm)].row = row;
            m[*totalm].col = col;
            m[*totalm].value = *sum;
            *sum = 0;
        }
    }
}
int compare(int n1,int n2){
    if(n1>n2) return 1;
    else if(n1==n2) return 0;
    return -1;
}
