#include <stdio.h>
#include <math.h>
#include "fixed_point_op.h"

// check fraction bits is enough
fixed_t float_to_fixed(float input, uint8_t fixed_bits, uint8_t fraction_bits)
{
    uint32_t max_integer;
    fixed_t output;
    uint32_t value;
    printf("\n-------Convert float to fixed-------------\n");
    printf("Set float %.2f to %d bits fixed point with fraction bits %d\n", input, fixed_bits, fraction_bits);
    max_integer = (1 << (fixed_bits - fraction_bits - 1)) - 1;
    if (fabs(input) > max_integer)
    {

        printf("\nInteger bits of %.2f is not enough!\nModify fraction bits %d to ", input, fraction_bits);
        fraction_bits = fixed_bits - int(log2((1 << fixed_bits) - fabs(int(input)))) + 1;
        printf("%d\n\n", fraction_bits);

        printf("Reset float %.2f to %d bits fixed point with fraction bits %d\n", input, fixed_bits, fraction_bits);
    }
    value = input * (1 << fraction_bits);
    output.fixed_bits = fixed_bits;
    output.fraction_bits = fraction_bits;
    output.value = MASK_BIT(value, fixed_bits);

    return output;
}

float fixed_to_float(fixed_t input)
{
    float output;

    if (MSB_BIT(input.value, input.fixed_bits))
    {
        uint32_t tmp;
        tmp = TWOSCOMP(input.value, input.fixed_bits);
        output = -(float)tmp/(1<<input.fraction_bits);
    }
    else
    {
        output = (float)input.value/(1<<input.fraction_bits);
    }

    return output;
}

// fixed point operation
fixed_t fixed_add(fixed_t fixed_a, fixed_t fixed_b)
{
    fixed_t output;
    uint8_t fraction_bits, fixed_bits;
    uint32_t tmp_fixed_a_bits, tmp_fixed_b_bits;
    uint32_t tmp_value_a, tmp_value_b, tmp_value;

    fraction_bits = (fixed_a.fraction_bits > fixed_b.fraction_bits) ? fixed_a.fraction_bits : fixed_b.fraction_bits;
    output.fraction_bits = fraction_bits;

    tmp_value_a = fixed_a.value << (fraction_bits - fixed_a.fraction_bits);
    tmp_value_b = fixed_b.value << (fraction_bits - fixed_b.fraction_bits);
    tmp_fixed_a_bits = fixed_a.fixed_bits + (fraction_bits - fixed_a.fraction_bits);
    tmp_fixed_b_bits = fixed_b.fixed_bits + (fraction_bits - fixed_b.fraction_bits);
    fixed_bits = tmp_fixed_a_bits > tmp_fixed_b_bits ? tmp_fixed_a_bits :tmp_fixed_b_bits;

    // add 1 bit to avoid overflow
    fixed_bits += 1;
    output.fixed_bits = fixed_bits;

    // if fixed point is positive mask with MAX_FIXED_BITS
    // if fixed point is neagtive fill 1 to MAX_FIXED_BITS
    if (MSB_BIT(tmp_value_a, tmp_fixed_a_bits))
    {
        tmp_value_a = FILL_ONE(tmp_value_a, fixed_bits, tmp_fixed_a_bits);
    }
    else
    {
        tmp_value_a = MASK_BIT(tmp_value_a, fixed_bits);
    }

    if (MSB_BIT(tmp_value_b, tmp_fixed_b_bits))
    {
        tmp_value_b = FILL_ONE(tmp_value_b, fixed_bits, tmp_fixed_b_bits);
    }
    else
    {
        tmp_value_b = MASK_BIT(tmp_value_b, fixed_bits);
    }

    output.value = MASK_BIT((tmp_value_a + tmp_value_b), output.fixed_bits);

    return output;
}

fixed_t fixed_mult(fixed_t fixed_a, fixed_t fixed_b)
{
    fixed_t output;
    uint32_t tmp_value_output, tmp_value_a, tmp_value_b;
    int8_t signed_a, signed_b;
    uint8_t fixed_bits;
    fixed_bits = fixed_a.fixed_bits + fixed_b.fixed_bits;

    if (MSB_BIT(fixed_a.value, fixed_a.fixed_bits))
    {
        tmp_value_a = TWOSCOMP(fixed_a.value, fixed_a.fixed_bits);
        signed_a = -1;
    }
    else
    {
        tmp_value_a = fixed_a.value;
        signed_a = 1;
    }

    if (MSB_BIT(fixed_b.value, fixed_b.fixed_bits))
    {
        tmp_value_b = TWOSCOMP(fixed_b.value, fixed_b.fixed_bits);
        signed_b = -1;
    }
    else
    {
        tmp_value_b = fixed_b.value;
        signed_b = 1;
    }

    tmp_value_output = MASK_BIT((tmp_value_a * tmp_value_b), fixed_bits);

    if ((signed_a * signed_b) == -1)
    {

        output.value = TWOSCOMP(tmp_value_output, fixed_bits);
    }
    else
    {
        output.value = tmp_value_output;
    }

    output.fixed_bits = fixed_bits;
    output.fraction_bits = fixed_a.fraction_bits + fixed_b.fraction_bits;

    return output;
}

fixed_t fixed_div(fixed_t fixed_a, fixed_t fixed_b)
{
    fixed_t output;
    uint32_t tmp_value_a, tmp_value_b, tmp_value;
    int8_t signed_a, signed_b;
    uint8_t diff_fraction_bits,fixed_bits, fraction_bits;

    if (MSB_BIT(fixed_a.value, fixed_a.fixed_bits))
    {
        tmp_value_a = TWOSCOMP(fixed_a.value, fixed_a.fixed_bits);
        signed_a = -1;
    }
    else
    {

        tmp_value_a = fixed_a.value;
        signed_a = 1;
    }

    if (MSB_BIT(fixed_b.value, fixed_b.fixed_bits))
    {
        tmp_value_b = TWOSCOMP(fixed_b.value, fixed_b.fixed_bits);
        signed_b = -1;
    }
    else
    {
        tmp_value_b = fixed_b.value;
        signed_b = 1;
    }
    
    output.fraction_bits = 0;
    
    if (fixed_a.fraction_bits == fixed_b.fraction_bits)
    {   
        
        
        fixed_bits = fixed_a.fixed_bits > fixed_b.fixed_bits ? fixed_a.fixed_bits: fixed_b.fixed_bits;
        tmp_value_a = MASK_BIT(tmp_value_a,fixed_bits);
        tmp_value_b = MASK_BIT(tmp_value_b,fixed_bits);
        output.fixed_bits = fixed_bits;
        

    }
    else if (fixed_a.fraction_bits > fixed_b.fraction_bits)
    {
        diff_fraction_bits = fixed_a.fraction_bits - fixed_b.fraction_bits;
        tmp_value_b = tmp_value_b << diff_fraction_bits;
        fixed_bits = fixed_a.fixed_bits > (fixed_b.fixed_bits+diff_fraction_bits) ? fixed_a.fixed_bits: (fixed_b.fixed_bits+diff_fraction_bits);
        tmp_value_a = MASK_BIT(tmp_value_a,fixed_bits);
        tmp_value_b = MASK_BIT(tmp_value_b,fixed_bits);
        output.fixed_bits = fixed_bits;


    }else{
        diff_fraction_bits = fixed_b.fraction_bits - fixed_a.fraction_bits;
        tmp_value_a = tmp_value_a << diff_fraction_bits;
        fixed_bits = fixed_b.fixed_bits > (fixed_a.fixed_bits+diff_fraction_bits) ? fixed_b.fixed_bits: (fixed_a.fixed_bits+diff_fraction_bits);
        tmp_value_a = MASK_BIT(tmp_value_a,fixed_bits);
        tmp_value_b = MASK_BIT(tmp_value_b,fixed_bits);
        output.fixed_bits = fixed_bits;

    }
    
    tmp_value = tmp_value_a / tmp_value_b;

    if ((signed_a * signed_b) == -1)
    {

        output.value = TWOSCOMP(tmp_value, output.fixed_bits);
    }
    else
    {
        output.value = tmp_value;
    }

    return output;
}
