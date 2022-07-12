#include <stdint.h>
#include <stdbool.h>

#define FIXED_BITS 8
#define MAX_FIXED_BITS 32
#define ROUND_OFF(x, bits) (x + (1 << (bits - 1))) >> bits
#define MSB_BIT(x, bits) x >> (bits - 1)
#define TWOSCOMP(x, bits) (((~x) + 1) & ((1 << bits) - 1))
#define MASK_BIT(x, bits) (x & ((1 << bits) - 1))
#define FILL_ONE(x, msb_bits, lsb_bits) (x | (((1 << (msb_bits - lsb_bits)) - 1) << lsb_bits))


//conversion between fixed and float
uint8_t float_to_fixed(float value,uint8_t fraction_bits);
float fixed_to_float(uint8_t value, uint8_t fraction_bits);

// check fraction bits is enough
bool check_fraction(float value, uint8_t* fraction_bits);

//fixed point operation
int8_t fixed_add(uint8_t value_a, uint8_t value_b, uint8_t fraction_a_bits, uint8_t fraction_b_bits);
int16_t fixed_mult(uint8_t value_a, uint8_t value_b, uint8_t fraction_a_bits, uint8_t fraction_b_bits);
int8_t fixed_div(uint8_t value_a, uint8_t value_b, uint8_t fraction_a_bits, uint8_t fraction_b_bits);

