#include <stdio.h>

#include <math.h>
#include <stdio.h>

int main() {
    double result;
    double num1 = 10.5;
    double num2 = 3.0;

    result = fmod(num1, num2);

    printf("The remainder of %f divided by %f is %f", num1, num2, result);

    return 0;
}