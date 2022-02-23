// Import header files
#include <stdio.h>
#include <stdlib.h>

long long** getMatrix(long long n)
{
    long long** mat = (long long**)malloc(n * sizeof(long long*));
    for (long long i = 0; i < n; i++)
        *(mat + i) = (long long*)malloc(n * sizeof(long long));

    printf("Enter element \n ");
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
        {
            scanf("%lld", &mat[i][j]);
        }
    return mat;
}

void calculate(long long** A, long long n, long long** filter, long long n1, long long cx, long long cy)
{
    // check if filter can be applied
    long long** temp = (long long**)malloc(n1 * sizeof(long long*));
    for (long long i = 0; i < n1; i++)
        *(temp + i) = (long long*)malloc(n1 * sizeof(long long));

    // check boundary values
    if (cx >= n1 / 2 && cx < (n - 1 / 2) && cy >= n1 / 2 && cy < (n - 1 / 2))
    {
        for (long long i = cx - n1 / 2; i <= cx + n1 / 2; i++)
        {
            for (long long j = 0; j < n1; j++)
            {
                long long sum = 0, k1 = 0;
                for (long long k = cy - n1 / 2; k <= cy + n1 / 2; k++)
                {
                    sum += A[i][k] * filter[k1][j];
                    k1++;
                }
                temp[i - cx + n1 / 2][j] = sum;
            }
        }
        for (long long i = cx - n1 / 2; i <= cx + n1 / 2; i++)
        {
            for (long long j = cy - n1 / 2; j <= cy + n1 / 2; j++)
            {
                A[i][j] = temp[i - cx + n1 / 2][j - cy + n1 / 2];
            }
        }
    }
}

void displayMatrix(long long** A, long long n)
{
    printf("\n");
    for (long long i = 0; i < n; i++)
    {
        for (long long j = 0; j < n; j++)
        {
            printf("%lld ", A[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    long long n = 5;

    // get matrix to be scaled to 128x128
    printf("Enter the large matrix : \n");
    long long** A = getMatrix(n);

    printf("Enter the small filter matrix : \n");
    long long** B = getMatrix(3);

    for (long long cx = 0; cx < n; cx++)
        for (long long cy = 0; cy < n; cy++)
            calculate(A, n, B, 3, cx, cy);

    // Display the modified matrix
    printf("Modified matrix is : \n");
    displayMatrix(A, n);

    return 0;
}