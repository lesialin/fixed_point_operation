# Fixed-Point Operation

This repo is for fixed point operation, the function include:

- fixed to float conversion
- float to fixed point convertion
- fixed point addition
- fixed point multiplication
- fixed point division


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
    f_a = 22.61f;
    f_b = -3.31f;
    fraction_a_bits = 1;
    fraction_b_bits = 2;
    fixed_bit = 8;

    
```

the result is as follows:

```
-------Convert float to fixed-------------
Set float 22.61 to 8 bits fixed point with fraction bits 1

-------Convert float to fixed-------------
Set float -3.31 to 8 bits fixed point with fraction bits 2

------Convert fixed point to float--------------
float 22.61 convert to fixed point 45, convert back to float 22.50
float -3.31 convert to fixed point 243, convert back to float -3.25

------------fixed addition--------------
fixed add: 22.50 + -3.25 = 19.25
float add: 22.61 + -3.31 = 19.30
the error of fixed add = 0.05

------------fixed multiplication--------------
fixed mult: 22.50 * -3.25 = -73.12
float mult: 22.61 * -3.31 = -74.84
the error of fixed multiplication = 1.71

------------fixed division--------------
fixed division: 22.50 / -3.25 = -6.00
float division: 22.61 / -3.31 = -6.83
the error of fixed division = 0.83

```