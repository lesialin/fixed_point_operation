# Fixed-Point Operation

This repo is for 8 bits fixed point operation, the function include:

- fixed to float conversion
- float to fixed point convertion
- fixed point addition
- fixed point multiplication
- fixed point division
- fraction bits check


**build**

```
mkdir build
cd build
cmake ..
cmake --build .

```
then you will get prebuilt/fixed_point_op.exe.

**usage**

the test pattern is in main.cpp, you can modify the test number as you need.

```
    f_a = -22.1f;
    f_b = -18.3f;
    fraction_a_bits = 3;
    fraction_b_bits = 2;
    
```

Remenber this is for 8 bits fixed point operation, 
carefully choose the fraction bits, and I also offer the check fraction function, like

```
-----------fraction bit check--------------

check fraction bit 3 for float -22.10
fraction bits too large, reduce fraction bits to 2

check fraction bit 2 for float -18.30
fraction bit is valid!

```

The operation result is like:

```
------------fixed float conversion--------------
float -22.10 convert to fixed 0xa8
float -18.30 convert to fixed 0xb7
fixed 0xa8 convert to float -23.00
fixed 0xb7 convert to float -19.00

------------fixed addition--------------
fixed add: 0xa8 + 0xb7 = -41
float add: -22.10 + -18.30 = -40.40
the error of fixed add = 0.60

------------fixed multiplication--------------
fixed mult: 0xa8 * 0xb7 = 402
float mult: -22.10 * -18.30 = 404.43
the error of fixed mult = 2.43

------------fixed division--------------
fixed div: 0xa8 / 0xb7 = 1
float div: -22.10 / -18.30 = 1.21
the error of fixed div = 0.21


```