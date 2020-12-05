#include<stdio.h>
#define MAX_TERMS 20000

typedef struct{
    float coefficient;
    float exponent;
}term;

typedef struct{
    int startIndex;
    int endIndex;
}polynomial;

term TERMS[MAX_TERMS];
int available{ 0 }; //Indicates first unoccupied index in TERMS array 

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
    polynomial p;
    p.startIndex = available;
    int i = p1.startIndex, j = p2.startIndex;

    for (;i <= p1.endIndex && j <= p2.endIndex;){
        if (TERMS[i].exponent < TERMS[j].exponent){
            TERMS[available++] = TERMS[i++];
        }
        else if (TERMS[i].exponent == TERMS[j].exponent){
            int coef = TERMS[i].coefficient + TERMS[j].coefficient;
            if(coef){
                TERMS[available].coefficient = coef;
                TERMS[available++].exponent = TERMS[i].exponent;
            } 
            i++;j++;
        }else{
            TERMS[available++] = TERMS[j++];
        }
    }

    while(i<=p1.endIndex){
        TERMS[available++] = TERMS[i++];
    }
    while(j<=p2.endIndex){
        TERMS[available++] = TERMS[j++];
    }

    p.endIndex = available-1;
    return p;
}

// – Cmult - multiply a polynomial by a const.
// – SingleMult - multiply a polynomial with a single term a.x^n

// – mult - multiply two polynomials

// – degree – returns the degree of the polynomial


