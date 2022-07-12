#include <stdio.h>
#include <math.h>
#include "fixed_point_op.h"

bool check_fraction(float value,uint8_t* fraction_bits)
{
    bool fraction_bits_valid = true;
    uint8_t max_integer;
    max_integer  = (1<<(FIXED_BITS-*fraction_bits-1))-1;
    if(fabs(value)> max_integer){
        *fraction_bits = FIXED_BITS - int(log2((1<<FIXED_BITS) - fabs(int(value)))) +1 ;
        fraction_bits_valid = false;
    }
    return fraction_bits_valid;
}

uint8_t float_to_fixed(float value, uint8_t fraction_bits)
{
    uint8_t output;
    output = value * (1 << fraction_bits);

    return output;
}

float fixed_to_float(uint8_t value, uint8_t fraction_bits)
{
    float output;

    if (MSB_BIT(value, FIXED_BITS))
    {
        uint8_t tmp;
        tmp = TWOSCOMP(value, FIXED_BITS);
        output = -ROUND_OFF(tmp, fraction_bits);
    }
    else
    {
        output = ROUND_OFF(value, fraction_bits);
    }

    return output;
}

int8_t fixed_add(uint8_t value_a, uint8_t value_b, uint8_t fraction_a_bits, uint8_t fraction_b_bits)
{
    int8_t output;
    uint8_t fraction_bits;
    uint8_t tmp_fixed_a_bits, tmp_fixed_b_bits;
    uint32_t tmp_value_a, tmp_value_b, tmp_output;

    fraction_bits = (fraction_a_bits > fraction_b_bits) ? fraction_a_bits : fraction_b_bits;

    tmp_value_a = value_a << (fraction_bits - fraction_a_bits);
    tmp_value_b = value_b << (fraction_bits - fraction_b_bits);
    tmp_fixed_a_bits = FIXED_BITS + (fraction_bits - fraction_a_bits);
    tmp_fixed_b_bits = FIXED_BITS + (fraction_bits - fraction_b_bits);

    if (MSB_BIT(tmp_value_a, tmp_fixed_a_bits))
    {
        tmp_value_a = FILL_ONE(tmp_value_a, MAX_FIXED_BITS, tmp_fixed_a_bits);
    }
    else
    {
        tmp_value_a = MASK_BIT(tmp_value_a, MAX_FIXED_BITS);
    }

    if (MSB_BIT(tmp_value_b, tmp_fixed_b_bits))
    {
        tmp_value_b = FILL_ONE(tmp_value_b, MAX_FIXED_BITS, tmp_fixed_b_bits);
    }
    else
    {
        tmp_value_b = MASK_BIT(tmp_value_b, MAX_FIXED_BITS);
    }

    tmp_output = tmp_value_a + tmp_value_b;

    if (MSB_BIT(tmp_output, MAX_FIXED_BITS))
    {
        uint32_t tmp;
        tmp = TWOSCOMP(tmp_output, MAX_FIXED_BITS);
        output = -ROUND_OFF(tmp, fraction_bits);
    }
    else
    {
        output = ROUND_OFF(tmp_output, fraction_bits);
    }

    return output;
}

int16_t fixed_mult(uint8_t value_a, uint8_t value_b, uint8_t fraction_a_bits, uint8_t fraction_b_bits)
{
    int16_t output;
    uint32_t tmp_value_output, tmp_value_a, tmp_value_b;
    int8_t signed_a, signed_b;

    if (MSB_BIT(value_a, FIXED_BITS))
    {
        tmp_value_a = TWOSCOMP(value_a, FIXED_BITS);
        signed_a = -1;
    }
    else
    {
        tmp_value_a = value_a;
        signed_a = 1;
    }

    if (MSB_BIT(value_b, FIXED_BITS))
    {
        tmp_value_b = TWOSCOMP(value_b, FIXED_BITS);
        signed_b = -1;
    }
    else
    {
        tmp_value_b = value_b;
        signed_b = 1;
    }

    output = (signed_a * signed_b) * ROUND_OFF(tmp_value_a * tmp_value_b, (fraction_a_bits + fraction_b_bits));

    return output;
}

int8_t fixed_div(uint8_t value_a, uint8_t value_b, uint8_t fraction_a_bits, uint8_t fraction_b_bits)
{
    int8_t output = 0;
    uint32_t tmp_value_a, tmp_value_b;
    int8_t signed_a, signed_b;

    if (MSB_BIT(value_a, FIXED_BITS))
    {
        tmp_value_a = TWOSCOMP(value_a, FIXED_BITS);
        signed_a = -1;
    }
    else
    {

        tmp_value_a = value_a;
        signed_a = 1;
    }

    if (MSB_BIT(value_b, FIXED_BITS))
    {
        tmp_value_b = TWOSCOMP(value_b, FIXED_BITS);
        signed_b = -1;
    }
    else
    {

        tmp_value_b = value_b;
        signed_b = 1;
    }

    if (fraction_a_bits > fraction_b_bits)
    {
        tmp_value_b = tmp_value_b << (fraction_a_bits - fraction_b_bits);
    }

    if (fraction_a_bits < fraction_b_bits)
    {
        tmp_value_a = tmp_value_a << (fraction_b_bits - fraction_a_bits);
    }

    output = tmp_value_a / tmp_value_b * (signed_a * signed_b);

    return output;
}
