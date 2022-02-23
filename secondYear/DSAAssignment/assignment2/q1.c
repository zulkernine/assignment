#include "polynomials.h"

int main(){
    polynomial p1, p2, padd, pmult;
    p1 = create_polynomial();
    printf("First poly: ");
    print_polynomial(p1);

    p2 = create_polynomial();
    printf("Second poly: ");
    print_polynomial(p2);

    padd = add(p1, p2);
    printf("Added: ");
    print_polynomial(padd);

    pmult = mult(p1, p2);
    printf("Multiplied: ");
    print_polynomial(pmult);

    printf("First poly: ");
    print_polynomial(p1);
    printf("Second poly: ");
    print_polynomial(p2);

    return 0;
}
