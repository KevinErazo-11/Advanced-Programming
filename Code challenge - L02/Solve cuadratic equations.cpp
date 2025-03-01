#include <iostream>
#include <cmath>

int main(){

    double a, b, c, x1, x2, discriminant;
    
    printf("ax^2 + bx + c = 0\n");
    printf("Enter the value of a: ");
    scanf("%lf", &a);
    printf("Enter the value of b: ");
    scanf("%lf", &b);
    printf("Enter the value of c: ");
    scanf("%lf", &c);

    if (a == 0) {
        printf("The value of 'a' must be non-zero.\n");
    } else {
        discriminant = pow(b, 2) - (4 * a * c);
        if (discriminant < 0) {
            printf("The equation has no real solutions.\n");
        } else {
            x1 = ((-1 * b) + sqrt(discriminant)) / (2 * a);
            x2 = ((-1 * b) - sqrt(discriminant)) / (2 * a);
            printf("\n -> (%lf)x^2 + (%lf)x + %lf = 0\n", a, b, c);
            printf("\n\t x1 = %.2f\n\tx2 = %.2f\n", x1, x2);
        }
    }

    return 0;
}
