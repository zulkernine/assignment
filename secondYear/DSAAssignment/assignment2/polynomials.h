#include<stdio.h>
#include <stdbool.h>

#define MAX_TERMS 20000 //Max lentgh of TERMS array which holds all polynomials
#define MAX_EXPO 1410065407

typedef struct{
    int coefficient;
    int exponent;
}term;

typedef struct{
    int startIndex;
    int endIndex;
}polynomial;

term TERMS[MAX_TERMS];
int available = 0; //Indicates first unoccupied index in TERMS array 

//Function declaration
bool isZero(polynomial p);
int coefficient(polynomial p, int exponent);
polynomial add(polynomial p1, polynomial p2);
polynomial cmult(polynomial p, double k);
polynomial singleMult(polynomial p, term t);
polynomial mult(polynomial p1, polynomial p2);
void print_polynomial(polynomial p);
polynomial create_polynomial();
term min_term(term* arr, int start, int end, int* index_of_first_occurence);


/*
    1.Each operation on polynomial will not alter the values of arguement polynomials.
    Instead it may return a new polynomial.

    2.All the terms will be in increasing order. Try to maintain this order
*/

// Is - zero – returns true if polynomial is zero.
bool isZero(polynomial p){
    if (p.startIndex == p.endIndex && TERMS[p.startIndex].coefficient == 0) return true;
    else return false;
}

// – Coef – returns the coeff.of a specified exponent.
int coefficient(polynomial p, int exponent){
    for (int i = p.startIndex;i <= p.endIndex;i++){
        if (TERMS[i].exponent == exponent) return TERMS[i].coefficient;
    }

    return 0;
}

// – add - add two polynomials
polynomial add(polynomial p1, polynomial p2){
    printf("add");
    polynomial p;
    p.startIndex = available;
    int i = p1.startIndex, j = p2.startIndex;

    for (;i <= p1.endIndex && j <= p2.endIndex;){
        if (TERMS[i].exponent < TERMS[j].exponent){
            TERMS[available++] = TERMS[i++];
        }
        else if (TERMS[i].exponent == TERMS[j].exponent){
            int coef = TERMS[i].coefficient + TERMS[j].coefficient;
            if (coef){
                TERMS[available].coefficient = coef;
                TERMS[available++].exponent = TERMS[i].exponent;
            }
            i++;j++;
        }
        else{
            TERMS[available++] = TERMS[j++];
        }
    }

    while (i <= p1.endIndex){
        TERMS[available++] = TERMS[i++];
    }
    while (j <= p2.endIndex){
        TERMS[available++] = TERMS[j++];
    }

    p.endIndex = available - 1;
    return p;
}

// – Cmult - multiply a polynomial by a const.
polynomial cmult(polynomial p, double k){
    for (int i = p.startIndex;i <= p.endIndex;i++) TERMS[i].coefficient *= k;
}

// – SingleMult - multiply a polynomial with a single term a.x^n
polynomial singleMult(polynomial p, term t){

    for (int i = p.startIndex;i <= p.endIndex;i++){
        TERMS[i].coefficient *= t.coefficient;
        TERMS[i].exponent += t.exponent;
    }
}

// – mult - multiply two polynomials
polynomial mult(polynomial p1, polynomial p2){
    polynomial p;
    p.startIndex = available;

    //First compute all the elements
    for (int i = p1.startIndex;i <= p1.endIndex;i++){
        for (int j = p2.startIndex;j <= p2.endIndex;j++){
            TERMS[available].coefficient = TERMS[i].coefficient * TERMS[j].coefficient;
            TERMS[available++].exponent = TERMS[i].exponent + TERMS[j].exponent;
        }
    }
    p.endIndex = available - 1;

    //Now merge all the terms with same exponent value
    int k = p.startIndex;
    int temp_index; term temp_t;  //to swap
    temp_t = min_term(TERMS, k, p.endIndex, &temp_index);
    TERMS[temp_index] = TERMS[k];
    TERMS[k] = temp_t;

    for (k = k + 1;k <= p.endIndex;k++){
        
        printf("init k:%d available:%d\n",k,available);
        temp_t = min_term(TERMS, k, p.endIndex, &temp_index);
        TERMS[temp_index] = TERMS[k];
        if (temp_t.exponent == MAX_EXPO){
            p.endIndex = k-1;
            available = k;
            break;
        }
        else{
            TERMS[k] = temp_t;
        }
        printf("k:%d available:%d\n", k, available);

    }

    return p;
}

// – degree – returns the degree of the polynomial

//print polynomial
void print_polynomial(polynomial p){
    for (int i = p.startIndex;i <= p.endIndex;i++){
        printf(" %+dx^%d", TERMS[i].coefficient, TERMS[i].exponent);
    }
    printf("\n");
}

//Create polynomial
polynomial create_polynomial(){
    int size;
    printf("No of terms: "); scanf("%d", &size);
    printf("Exponent must be in increasing order\n\n");

    polynomial p;
    p.startIndex = available;
    for (int i = 0;i < size;i++){
        printf("Enter coefficient and exponent(separated by space): ");
        scanf("%d %d", &(TERMS[available].coefficient), &(TERMS[available].exponent));
        available++;
    }
    p.endIndex = available - 1;
    return p;
}

/* Internal Function */
term min_term(term* arr, int start, int end, int* index_of_first_occurence){
    term t = TERMS[start];
    for (int i = start + 1;i <= end;i++){
        if (TERMS[i].exponent < t.exponent){
            t.exponent = TERMS[i].exponent;
            t.coefficient = TERMS[i].coefficient;
            *index_of_first_occurence = i;
            TERMS[i].exponent = MAX_EXPO;
        }
        else if (TERMS[i].exponent == t.exponent){
            t.coefficient += TERMS[i].coefficient;
            TERMS[i].exponent = MAX_EXPO;
        }
    }

    return t;
}
