#include <stdio.h>
#include <math.h>
#include "fixed_point_op.h"

int main()
{
    bool fraction_bit_valid;
    float f_a, f_b;
    int8_t output, output3;
    int16_t output2;
    float output_f, output_f2, output_f3;

    uint8_t fixed_a, fixed_b;
    uint8_t fraction_a_bits, fraction_b_bits;

    f_a = -22.1f;
    f_b = -18.3f;
    fraction_a_bits = 3;
    fraction_b_bits = 2;
    printf("\n-----------fraction bit check--------------\n");
    printf("\ncheck fraction bit %d for float %.2f\n", fraction_a_bits, f_a);
    fraction_bit_valid = check_fraction(f_a, &fraction_a_bits);

    if (fraction_bit_valid)
    {
        printf("fraction bit is valid!\n");
    }
    else
    {
        printf("fraction bits too large, reduce fraction bits to %d\n", fraction_a_bits);
    }

    printf("\ncheck fraction bit %d for float %.2f\n", fraction_b_bits, f_b);
    fraction_bit_valid = check_fraction(f_b, &fraction_b_bits);
    if (fraction_bit_valid)
    {
        printf("fraction bit is valid!\n");
    }
    else
    {
        printf("fraction bits too large, reduce fraction bits to %d\n", fraction_b_bits);
    }
    // fixed point coversion
    fixed_a = float_to_fixed(f_a, fraction_a_bits);
    fixed_b = float_to_fixed(f_b, fraction_b_bits);

    printf("\n------------fixed float conversion--------------\n");
    printf("float %.2f convert to fixed 0x%x\n", f_a, fixed_a);
    printf("float %.2f convert to fixed 0x%x\n", f_b, fixed_b);
    printf("fixed 0x%x convert to float %.2f\n", fixed_a, fixed_to_float(fixed_a, fraction_a_bits));
    printf("fixed 0x%x convert to float %.2f\n", fixed_b, fixed_to_float(fixed_b, fraction_b_bits));

    printf("\n------------fixed addition--------------\n");
    output = fixed_add(fixed_a, fixed_b, fraction_a_bits, fraction_b_bits);
    output_f = f_a + f_b;
    printf("fixed add: 0x%x + 0x%x = %d\n", fixed_a, fixed_b, output);
    printf("float add: %.2f + %.2f = %.2f\n", f_a, f_b, output_f);
    printf("the error of fixed add = %.2f\n", fabs(output - output_f));

    printf("\n------------fixed multiplication--------------\n");
    output2 = fixed_mult(fixed_a, fixed_b, fraction_a_bits, fraction_b_bits);
    output_f2 = f_a * f_b;
    printf("fixed mult: 0x%x * 0x%x = %d\n", fixed_a, fixed_b, output2);
    printf("float mult: %.2f * %.2f = %.2f\n", f_a, f_b, output_f2);
    printf("the error of fixed mult = %.2f\n", fabs(output2 - output_f2));

    printf("\n------------fixed division--------------\n");
    output3 = fixed_div(fixed_a, fixed_b, fraction_a_bits, fraction_b_bits);
    output_f3 = f_a / f_b;
    printf("fixed div: 0x%x / 0x%x = %d\n", fixed_a, fixed_b, output3);
    printf("float div: %.2f / %.2f = %.2f\n", f_a, f_b, output_f3);
    printf("the error of fixed div = %.2f\n", fabs(output3 - output_f3));

    return 0;
}