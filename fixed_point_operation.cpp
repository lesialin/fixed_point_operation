#include <stdio.h>
#include "fixed_point_operation.h"

uint16_t float_to_fixed16_t(float f_value, uint16_t fraction){
    return (uint16_t)(f_value*(1<<fraction));
}


void example_fixed_int_mut(uint16_t i_a, float f_a){
    uint16_t fixed_a;
    uint16_t i_b;

    fixed_a = float_to_fixed16_t(f_a,VAR_A_FIXED_16_FRACTION_BITS);

    i_b = (uint16_t)(f_a *i_a);
    printf("origin:  %d x %f = %d\n", i_a, f_a,i_b);

    i_b = fixed_a * i_a >> VAR_A_FIXED_16_FRACTION_BITS;
    printf("fixed:  %d x %f = %d\n", i_a, f_a,i_b);


}

void example_fixed_fixed_add(){

}

void example_fixed_fixed_mut(){

}