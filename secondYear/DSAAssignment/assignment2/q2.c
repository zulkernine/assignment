#include"sparse-matrix.h"

void inputMatrix(matrix_term* matrix){
    printf("Eneter row column and number of non-zero terms space separated(r c n): ");
    scanf("%d %d %f", &(matrix[0].row), &(matrix[0].col), &(matrix[0].value));
    printf("Enter %d terms space separated, each in a new line:\n",(int)matrix[0].value);
    for (int i = 1;i <= matrix[0].value;i++){
        printf("row col value : ");
        scanf("%d %d %f",&(matrix[i].row),&(matrix[i].col),&(matrix[i].value));
    }
}

int main(){
    matrix_term *mtx1,*mtx2,*addm,*transm;

    mtx1=create_matrix(); mtx2=create_matrix();
    inputMatrix(mtx1);inputMatrix(mtx2);

    printf("Matrix1:\n");print_matrix(mtx1); 
    printf("Matrix2:\n");print_matrix(mtx2);

    addm = add_matrix(mtx1,mtx2);
    printf("\n\nAdded matrix:\n\n");
    print_matrix(addm);

    transm = transpose(addm);
    printf("\n\nTranspose of added matrix:\n\n");
    print_matrix(transm);

    return 0;
}