#include <stdio.h>
#include <stdbool.h>

#define MAX_TERMS 20000 //Max lentgh of TERMS array which holds all polynomials
#define MAX_EXPO 1410065407

typedef struct
{
    int coefficient;
    int exponent;
} term;

typedef struct
{
    int startIndex;
    int endIndex;
} polynomial;

term TERMS[MAX_TERMS];
int available = 0; //Indicates first unoccupied index in TERMS array

//Function declaration
bool isZero(polynomial p);
int coefficient(polynomial p, int exponent);
polynomial add(polynomial p1, polynomial p2);
void cmult(polynomial p, double k);
void singleMult(polynomial p, term t);
polynomial mult(polynomial p1, polynomial p2);
void print_polynomial(polynomial p);
polynomial create_polynomial();
term min_term(term* arr, int start, int end, int* index_of_first_occurence);
void mergesort(term* arr, int start, int end);
void merge(term* arr, int start, int mid, int end);

/*
    1.Each operation on polynomial will not alter the values of arguement polynomials.
    Instead it may return a new polynomial.

    2.All the terms will be in increasing order. Try to maintain this order
*/

// Is - zero – returns true if polynomial is zero.
bool isZero(polynomial p)
{
    if (p.startIndex == p.endIndex && TERMS[p.startIndex].coefficient == 0)
        return true;
    else
        return false;
}

// – Coef – returns the coeff.of a specified exponent.
int coefficient(polynomial p, int exponent)
{
    for (int i = p.startIndex; i <= p.endIndex; i++)
    {
        if (TERMS[i].exponent == exponent)
            return TERMS[i].coefficient;
    }

    return 0;
}

// – add - add two polynomials
polynomial add(polynomial p1, polynomial p2)
{
    printf("add");
    polynomial p;
    p.startIndex = available;
    int i = p1.startIndex, j = p2.startIndex;

    for (; i <= p1.endIndex && j <= p2.endIndex;)
    {
        if (TERMS[i].exponent < TERMS[j].exponent)
        {
            TERMS[available++] = TERMS[i++];
        }
        else if (TERMS[i].exponent == TERMS[j].exponent)
        {
            int coef = TERMS[i].coefficient + TERMS[j].coefficient;
            if (coef)
            {
                TERMS[available].coefficient = coef;
                TERMS[available++].exponent = TERMS[i].exponent;
            }
            i++;
            j++;
        }
        else
        {
            TERMS[available++] = TERMS[j++];
        }
    }

    while (i <= p1.endIndex)
    {
        TERMS[available++] = TERMS[i++];
    }
    while (j <= p2.endIndex)
    {
        TERMS[available++] = TERMS[j++];
    }

    p.endIndex = available - 1;
    return p;
}

// – Cmult - multiply a polynomial by a const.
void cmult(polynomial p, double k)
{
    for (int i = p.startIndex; i <= p.endIndex; i++)
        TERMS[i].coefficient *= k;

}

// – SingleMult - multiply a polynomial with a single term a.x^n
void singleMult(polynomial p, term t)
{

    for (int i = p.startIndex; i <= p.endIndex; i++)
    {
        TERMS[i].coefficient *= t.coefficient;
        TERMS[i].exponent += t.exponent;
    }
}

// – mult - multiply two polynomials
polynomial mult(polynomial p1, polynomial p2)
{
    polynomial p;
    p.startIndex = available;

    //First compute all the elements
    for (int i = p1.startIndex; i <= p1.endIndex; i++)
    {
        for (int j = p2.startIndex; j <= p2.endIndex; j++)
        {
            TERMS[available].coefficient = TERMS[i].coefficient * TERMS[j].coefficient;
            TERMS[available++].exponent = TERMS[i].exponent + TERMS[j].exponent;
        }
    }
    p.endIndex = available - 1;

    //Now merge all the terms with same exponent value
    mergesort(TERMS, p.startIndex, p.endIndex);
    int i = p.startIndex, j = p.startIndex + 1;
    while (j <= p.endIndex)
    {
        if (TERMS[i].exponent == TERMS[j].exponent)
        {
            TERMS[i].coefficient += TERMS[j].coefficient;
            j++;
        }
        else
        {
            ++i;
            TERMS[i] = TERMS[j];
            j++;
        }
    }
    p.endIndex = i;
    available = i + 1;

    return p;
}

// – degree – returns the degree of the polynomial

//print polynomial
void print_polynomial(polynomial p){
    for (int i = p.startIndex;i <= p.endIndex;i++){
        if (TERMS[i].exponent)
            printf(" %+dx^%d", TERMS[i].coefficient, TERMS[i].exponent);
        else
            printf("%+d", TERMS[i].coefficient);
    }
    printf("\n");
}

//Create polynomial
polynomial create_polynomial()
{
    int size;
    printf("No of terms: ");
    scanf("%d", &size);
    printf("Exponent must be in increasing order\n\n");

    polynomial p;
    p.startIndex = available;
    for (int i = 0; i < size; i++)
    {
        printf("Enter coefficient and exponent(separated by space): ");
        scanf("%d %d", &(TERMS[available].coefficient), &(TERMS[available].exponent));
        available++;
    }
    p.endIndex = available - 1;
    return p;
}

//Merge Sort The Terms array for a specific polynomial
void mergesort(term* arr, int start, int end)
{
    if (start == end)
    {
        return;
    }
    int mid;
    mid = (start + end) / 2;

    mergesort(arr, start, mid);
    mergesort(arr, mid + 1, end);

    merge(arr, start, mid, end);
}

void merge(term* arr, int start, int mid, int end)
{
    int n1 = (mid - start + 1), n2 = (end - mid);
    term temp_arr1[n1], temp_arr2[n2];

    for (int i = 0; i < n1; i++)
        temp_arr1[i] = arr[start + i];
    for (int j = 0; j < n2; j++)
        temp_arr2[j] = arr[mid + 1 + j];

    int k = start, i = 0, j = 0;
    while (i < n1 && j < n2)
    {
        if (temp_arr1[i].exponent < temp_arr2[j].exponent)
        {
            arr[k] = temp_arr1[i];
            i++;
        }
        else
        {
            arr[k] = temp_arr2[j];
            j++;
        }
        k++;
    }

    while (i < n1)
        arr[k++] = temp_arr1[i++];
    while (j < n2)
        arr[k++] = temp_arr2[j++];
}
