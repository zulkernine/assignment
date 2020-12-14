#include "polynomials.h"

int main(){
    polynomial p1,p2,padd,pmult;
    p1 = create_polynomial();
    p2 = create_polynomial();

    padd = add(p1,p2);
    pmult = mult(p1,p2);

    printf("First poly: ");
    print_polynomial(p1);
    printf("Second poly: ");
    print_polynomial(p2);

    printf("Added: ");
    print_polynomial(padd);
    printf("Multiplied: ");
    print_polynomial(pmult);
    printf("%d,%d\n",pmult.startIndex,pmult.endIndex);
    return 0;
}
