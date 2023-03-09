#include <riscv_vector.h>
#include <stdio.h>
#include "utils.c"
#include <math.h>

int main() {
    /**
    * Vector Single-Width Saturating Add and Subtract Functions  -  352 intrinsics
    * Vector Single-Width Averaging Add and Subtract Functions - 352 intrinsics
    * Vector Single-Width Fractional Multiply with Rounding and Saturation Functions - 88 intrinsics
    * Vector Single-Width Scaling Shift Functions - 176 intrinsics
    * Vector Narrowing Fixed-Point Clip Functions - 120 intrinsics
    **/

    __int32_t a[] = {1,2,3,4};
    __int32_t b[] = {8,7,6,5};
    __int32_t max[] = {2147483647,2147483647,2147483647,2147483647};

    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    vint32m1_t v_max = vle32_v_i32m1 (max, vl);
    // Saturating Add
    vint32m1_t v_sadd = vsadd_vv_i32m1 (v_a, v_max, vl);
    dump_i32_vector(v_sadd, vl);

    // Averaging Add
    // roundoff_unsigned(vs2[i] + vs1[i], 1)
    vint32m1_t v_aadd = vaadd_vv_i32m1 (v_a, v_b, vl);
    dump_i32_vector(v_aadd, vl);


    printf("Fractional Multiply with Rounding and Saturation Test \n");
    // Fractional Multiply with Rounding and Saturation
    float f[] = {0.1, 0.2, 0.3, 0.4};
    __int32_t q[4] = {0};
    long _power_2_31 = pow(2,31); // 2147483648
    // quantize
    q[0] = f[0] * _power_2_31;
    q[1] = f[1] * _power_2_31;
    q[2] = f[2] * _power_2_31;
    q[3] = f[3] * _power_2_31;

    vint32m1_t v_q = vle32_v_i32m1(q, vl);
    // [214748368] [429496736] [644245120] [858993472] 
    dump_i32_vector(v_q, vl);

    // [21474837] [85899348] [193273544] [343597394] 
    vint32m1_t v_smul = vsmul_vv_i32m1 (v_q, v_q, vl);
    dump_i32_vector(v_smul, vl);
    __int32_t result[4] = {0};
    vse32_v_i32m1(result, v_smul,vl);
    // dequantize
    // 0.010000 0.040000 0.090000 0.160000 
    printf("%f %f %f %f \n",(float)result[0]/_power_2_31, (float)result[1]/_power_2_31
            , (float)result[2]/_power_2_31, (float)result[3]/_power_2_31);

    // Vector Single-Width Scaling Shift Functions
    // fixed point right shift
    // [21474837] [85899348] [193273544] [343597394] >> 2
    // [5368709] [21474837] [48318386] [85899349] 
    dump_i32_vector(vssra_vx_i32m1 (v_smul, 2, vl),vl);

    // Vector Narrowing Fixed-Point Clip Functions
    // [328] [1311] [2949] [5243] / 2^15
    //= 0.010000 0.040000 0.090000 0.160000 
    dump_i16mf2_vector( vnclip_wx_i16mf2 (v_smul, 16, vl), vl);

    return 0;
}