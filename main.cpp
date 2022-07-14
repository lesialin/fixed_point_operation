#include <stdio.h>
#include <math.h>
#include "fixed_point_op.h"

int main()
{
    bool fraction_bit_valid;
    float f_a, f_b;
    float output_f, output_f2, output_f3;

    fixed_t fixed_a, fixed_b;
    fixed_t output,output2, output3;
    uint8_t fixed_bit,fraction_a_bits, fraction_b_bits;

    f_a = 22.61f;
    f_b = -3.31f;
    fraction_a_bits = 1;
    fraction_b_bits = 2;
    fixed_bit = 8;

    // fixed point coversion
    fixed_a = float_to_fixed(f_a, fixed_bit, fraction_a_bits);
    fixed_b = float_to_fixed(f_b, fixed_bit, fraction_b_bits);

    printf("\n------Convert fixed point to float--------------\n");

    
    printf("float %.2f convert to fixed point %d, convert back to float %.2f\n", f_a, fixed_a.value,fixed_to_float(fixed_a));
    printf("float %.2f convert to fixed point %d, convert back to float %.2f\n", f_b, fixed_b.value,fixed_to_float(fixed_b));

    printf("\n------------fixed addition--------------\n");
    output = fixed_add(fixed_a, fixed_b);
    output_f = f_a + f_b;
    printf("fixed add: %.2f + %.2f = %.2f\n", fixed_to_float(fixed_a), fixed_to_float(fixed_b), fixed_to_float(output));
    printf("float add: %.2f + %.2f = %.2f\n", f_a, f_b, output_f);
    printf("the error of fixed add = %.2f\n", fabs(fixed_to_float(output) - output_f));

    printf("\n------------fixed multiplication--------------\n");
    output2 = fixed_mult(fixed_a, fixed_b);
    output_f2 = f_a * f_b;
    printf("fixed mult: %.2f * %.2f = %.2f\n", fixed_to_float(fixed_a), fixed_to_float(fixed_b), fixed_to_float(output2));
    printf("float mult: %.2f * %.2f = %.2f\n", f_a, f_b, output_f2);
    printf("the error of fixed multiplication = %.2f\n", fabs(fixed_to_float(output2) - output_f2));


    printf("\n------------fixed division--------------\n");
    output3 = fixed_div(fixed_a, fixed_b);
    output_f3 = f_a / f_b;
    printf("fixed division: %.2f / %.2f = %.2f\n", fixed_to_float(fixed_a), fixed_to_float(fixed_b), fixed_to_float(output3));
    printf("float division: %.2f / %.2f = %.2f\n", f_a, f_b, output_f3);
    printf("the error of fixed division = %.2f\n", fabs(fixed_to_float(output3) - output_f3));


    return 0;
}