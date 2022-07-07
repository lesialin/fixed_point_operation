#include <stdio.h>
#include "fixed_point_operation.h"



int main(){
    float f_a;
    uint16_t i_a;
    
    f_a = 0.87f;
    i_a = 48;
    
    example_fixed_int_mut(i_a, f_a);
    
    return 0;
}