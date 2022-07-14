#include <stdint.h>
#include <stdbool.h>


#define ROUND_OFF(x, bits) (x + (1 << (bits - 1))) >> bits
#define MSB_BIT(x, bits) x >> (bits - 1)
#define TWOSCOMP(x, bits) (((~x) + 1) & ((1 << bits) - 1))
#define MASK_BIT(x, bits) (x & ((1 << bits) - 1))
#define FILL_ONE(x, msb_bits, lsb_bits) (x | (((1 << (msb_bits - lsb_bits)) - 1) << lsb_bits))

typedef struct fixed_t{
    uint8_t fixed_bits;
    uint8_t fraction_bits;
    uint32_t value;
};


fixed_t float_to_fixed(float value,uint8_t fixed_bits, uint8_t fraction_bits);
float fixed_to_float(fixed_t input);

//fixed point operation
fixed_t fixed_add(fixed_t fixed_a, fixed_t fixed_b);
fixed_t fixed_mult(fixed_t fixed_a,fixed_t fixed_b);
fixed_t fixed_div(fixed_t fixed_a, fixed_t fixed_b);


