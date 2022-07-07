#include <stdint.h>

// fixed_16 format 15.1
#define VAR_A_FIXED_16_FRACTION_BITS 15
// fixed_16 format 12.4
#define VAR_B_FIXED_16_FRACTION_BITS 12

uint16_t float_to_fixed16_t(float f_value, uint16_t fraction);


void example_fixed_int_mut(uint16_t i_a, float f_a);
void example_fixed_fixed_add();
void example_fixed_fixed_mut();