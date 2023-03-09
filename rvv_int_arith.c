#include <riscv_vector.h>
#include <stdio.h>
#include <utils.c>

/** RISCV-V-SPEC-1.0:
* Vector Single-Width Integer Add and Subtract
* Vector Widening Integer Add/Subtract
* Vector Integer Extension
* Vector Integer Add-with-Carry / Subtract-with-Borrow Instructions
* Vector Bitwise Logical Instructions
* Vector Single-Width Shift Instructions
* Vector Narrowing Integer Right Shift Instructions
* Vector Integer Compare Instructions
* Vector Integer Min/Max Instructions
* Vector Single-Width Integer Multiply Instructions
* Vector Integer Divide Instructions
* Vector Widening Integer Multiply Instructions
* Vector Single-Width Integer Multiply-Add Instructions
* Vector Widening Integer Multiply-Add Instructions
* Vector Integer Merge Instructions
* Vector Integer Move Instructions
*/

const __int32_t a[] = {1,2,3,4};
const __int32_t b[] = {8,7,6,5};


//Vector Single-Width Integer Add and Subtract
void vswias() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);

    printf("Test Vector Single-Width Integer Add and Subtract \n");

    // a+b
    vint32m1_t a_plus_b = vadd_vv_i32m1 (v_a, v_b, vl);
    dump_i32_vector(a_plus_b, vl);

    // a-b
    vint32m1_t a_sub_b = vsub_vv_i32m1 (v_a, v_b, vl);
    dump_i32_vector(a_sub_b, vl);

    // vector - scaler
    vint32m1_t a_sub_1 = vsub_vx_i32m1 (v_a, 1, vl);
    dump_i32_vector(a_sub_1, vl);

    // -(vector - scaler)
    vint32m1_t a_rsub_1 = vrsub_vx_i32m1 (v_a, 1, vl);
    dump_i32_vector(a_rsub_1, vl);

    // -vector
    vint32m1_t a_neg = vneg_v_i32m1 (v_a, vl);
    dump_i32_vector(a_neg, vl);
}

//Vector Widening Integer Add/Subtract
void vwias() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);

    printf("Test Vector Widening Integer Add/Subtract \n");

    vint64m2_t a_add_b_w = vwadd_vv_i64m2 (v_a, v_b, vl);
    dump_i64m2_vector(a_add_b_w, vl);
}

void vie() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);

    printf("Vector Integer Extension \n");

    vint64m2_t a_ext = vsext_vf2_i64m2 (v_a, vl);
    dump_i64m2_vector(a_ext, vl);
}

// Vector Integer Add-with-Carry / Subtract-with-Borrow Instructions
void viawc_swb() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    printf("Vector Integer Add-with-Carry \n");

    // generate a vbool32_t
    // [1111]
    vbool32_t carryin = vmseq_vv_i32m1_b32(v_a, v_a, vl);
    // 1+8+1,2+7+1,3+6+1,4+5+1
    // [10] [10] [10] [10] 
    vint32m1_t v_dst =  vadc_vvm_i32m1 (v_a, v_b, carryin,vl);
    dump_i32_vector(v_dst, vl);

    // v_a - v_b - borrowin
    // 1-8-1, 2-7-1, 3-6-1, 4-5-1
    // [-8] [-6] [-4] [-2] 
    v_dst =  vsbc_vvm_i32m1 (v_a, v_b, carryin,vl);
    dump_i32_vector(v_dst, vl);
}

// Vector Bitwise Logical Instructions
void vbli() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    printf("Vector Bitwise Logical Instructions \n");

    // a = 1 2 3 4 => 0001 0010 0011 0100
    // b = 8 7 6 5 => 1000 0111 0110 0101
    //   a & b  = >   0000 0010 0010 0100  => [0 2 2 4]
    vint32m1_t a_and_b = vand_vv_i32m1 (v_a, v_b, vl);
    dump_i32_vector(a_and_b, vl);

}

// Vector Single-Width Shift Instructions
void vswsi(){
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vuint32m1_t v_b = vle32_v_u32m1 (b, vl);
    printf("Vector Single-Width Shift Instructions \n");

    // a = 1 2 3 4
    // b = 8 7 6 5
    // a << b  = > 1 * 2^8, 2 * 2^7, 3 * 2^6, 4 * 2^5 => 256 256 192 128
    vint32m1_t a_sll_b = vsll_vv_i32m1 (v_a, v_b, vl);
    dump_i32_vector(a_sll_b, vl);
}

// Vector Narrowing Integer Right Shift Instructions
void vnirsi() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    printf("Vector Narrowing Integer Right Shift Instructions\n");
    // b = 8 7 6 5 => 1000 0111 0110 0101 >> 1 => 0100 0011 0011 0010 => 4 3 3 2
    vint16mf2_t v_b_narrowing = vnsra_wx_i16mf2 (v_b, 1, vl);
    dump_i16mf2_vector(v_b_narrowing, vl);
}

// Vector Integer Compare Instructions
void vici() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    printf("Vector Integer Compare Instructions\n");
    vbool32_t vbool = vmseq_vv_i32m1_b32 (v_a, v_b, vl);

    uint8_t array[4] = {0,0,0,0};
    vsm_v_b32 (array, vbool, 4);
    printBinary(array[0]);

    vbool = vmseq_vv_i32m1_b32 (v_a, v_a, vl);
    vsm_v_b32 (array, vbool, 4);
    printBinary(array[0]);

    int c[4] = {1,1,3,3};
    //    a  = 1 2 3 4
    //    c  = 1 1 3 3
    // vbool = 1 0 1 0
    vint32m1_t v_c = vle32_v_i32m1 (c, vl);
    vbool = vmseq_vv_i32m1_b32 (v_a, v_c, vl);
    vsm_v_b32 (array, vbool, 4);
    printBinary(array[0]);
}

// Vector Integer Min/Max Instructions
void vimmi() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    printf("Vector Integer Min/Max Instructions\n");

    vint32m1_t v_min = vmin_vv_i32m1 (v_a, v_b, vl);
    dump_i32_vector(v_min, vl);
}

// Vector Single-Width Integer Multiply Instructions
void vswimi() {
    int8_t i8a[16] = {20, 30, 100, 120};
    int8_t i8b[16] = {2, 3, 100, 120};
    vint8m1_t v_a = vle8_v_i8m1(i8a, 4);
    vint8m1_t v_b = vle8_v_i8m1(i8b, 4);
    printf("Vector Single-Width Integer Multiply Instructions\n");

    // A * B not saturated

    // 100 * 100 = 10000 = 0010 0111 0001 0000
    // low 8bit = 00010000 = 16
    // high 8b  = 00100111 = 39

    // [40] [90] [16] [64]
    vint8m1_t v_ab_low = vmul_vv_i8m1 (v_a, v_b, 4);
    dump_i8_vector(v_ab_low, 4);
    // [0] [0] [39] [56]
    vint8m1_t v_ab_high = vmulh_vv_i8m1 (v_a, v_b, 4);
    dump_i8_vector(v_ab_high, 4);
}

// Vector Integer Divide Instructions
void vidi() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    printf("Vector Integer Divide Instructions\n");

    // v_b = 8 7 6 5
    // v_a = 1 2 3 4
    // v_b / v_a = 8 3 2 1
    dump_i32_vector(vdiv_vv_i32m1(v_b, v_a, vl), vl);
    // v_b % v_a = 0 1 0 1
    dump_i32_vector(vrem_vv_i32m1(v_b, v_a, vl), vl);

}

// Vector Widening Integer Multiply Instructions
void vwimi() {
    int32_t i32a[4] = {1000, 2000, 3000, 4000};
    int32_t i32_max = 2147483647;
    vint32m1_t v_a = vle32_v_i32m1(i32a, 4);
    printf("Vector Widening Integer Multiply Instructions\n");

    // A * B => 2 times SEW result
    // [2147483647000] [4294967294000] [6442450941000] [8589934588000]
    vint64m2_t v_a_max = vwmul_vx_i64m2(v_a, i32_max, 4);
    dump_i64m2_vector(v_a_max, 4);
}

// Vector Single-Width Integer Multiply-Add Instructions
void vswimai() {
    int c[4] = {3,4,5,6};
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    vint32m1_t v_c = vle32_v_i32m1 (c, vl);

    printf("Vector Single-Width Integer Multiply-Add Instructions\n");

    // v_a = 1 2 3 4
    // v_b = 8 7 6 5
    // v_c = 3 4 5 6
    // a + b * c = [25] [30] [33] [34]
    dump_i32_vector(vmacc_vv_i32m1 (v_a, v_b, v_c, vl), vl);
    // a * b + c = [11] [18] [23] [26]
    dump_i32_vector(vmadd_vv_i32m1 (v_a, v_b, v_c, vl), vl);
}

// Vector Widening Integer Multiply-Add Instructions
void vwimai() {
    int64_t c[4] = {3,4,5,6};
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);
    vint64m2_t v_c = vle64_v_i64m2 (c, vl);

    printf("Vector Widening Integer Multiply-Add Instructions\n");

    // v_a = 1 2 3 4
    // v_b = 8 7 6 5
    // v_c = 3 4 5 6
    // c + a * b = [11] [18] [23] [26]
    dump_i64m2_vector(vwmacc_vv_i64m2 (v_c, v_a, v_b, vl), vl);
}

// Vector Integer Merge Instructions
void vimi() {
    printf("Vector Integer Merge Instructions\n");
    size_t vl = vsetvlmax_e8m1();
    uint8_t mask[2] = {170,170};
    int8_t i8a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int8_t i8b[16] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
    vint8m1_t v_a = vle8_v_i8m1(i8a, vl);
    vint8m1_t v_b = vle8_v_i8m1(i8b, vl);

    // vlm.v vd, (rs1)   #  Load byte vector of length ceil(vl/8)
    vbool8_t vmask = vlm_v_b8 (mask, vl);
    // vmerge.vvm vd, vs2, vs1, v0  # vd[i] = v0.mask[i] ? vs1[i] : vs2[i]
    vint8m1_t v_merged = vmerge_vvm_i8m1 (vmask, v_a, v_b, vl);
    // [1] [12] [3] [14] [5] [16] [7] [18] [9] [20] [11] [22] [13] [24] [15] [26]
    dump_i8_vector(v_merged, vl);

    // https://github.com/riscv/riscv-v-spec/blob/master/v-spec.adoc#1115-vector-integer-merge-instructions
    // if mask[i] is 1 then v_merged[i] = v_a[i], otherwize v_b[i]
    //
    // 1. load mask[170, 170] to v0
    //(gdb) p $v0  { b = {170, 170, 0 <repeats 14 times>}}
    // 2. convert mask to binary:
    // 10101010 10101010
    // so result is a b a b a b a b...
}

// Vector Integer Move Instructions
void vimoi() {
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1(a, vl);

    printf("Vector Integer Move Instructions\n");
    vint32m1_t v_dst = vmv_v_v_i32m1(v_a, vl);
    // [1] [2] [3] [4]
    dump_i32_vector(v_dst, vl);

    v_dst = vmv_v_x_i32m1(25, vl);
    // [25] [25] [25] [25]
    dump_i32_vector(v_dst, vl);
}

int main() {
    // Vector Single-Width Integer Add and Subtract
    vswias();
    // Vector Widening Integer Add/Subtract
    vwias();
    // Vector Integer Extension
    vie();
    // Vector Integer Add-with-Carry / Subtract-with-Borrow Instructions
    viawc_swb();
    // Vector Bitwise Logical Instructions
    vbli();
    // Vector Single-Width Shift Instructions
    vswsi();
    // Vector Narrowing Integer Right Shift Instructions
    vnirsi();
    // Vector Integer Compare Instructions
    vici();
    // Vector Integer Min/Max Instructions
    vimmi();
    // Vector Single-Width Integer Multiply Instructions
    vswimi();
    // Vector Integer Divide Instructions
    vidi();
    // Vector Widening Integer Multiply Instructions
    vwimi();
    // Vector Single-Width Integer Multiply-Add Instructions
    vswimai();
    // Vector Widening Integer Multiply-Add Instructions
    vwimai();
    // Vector Integer Merge Instructions
    vimi();
    // Vector Integer Move Instructions
    vimoi();

    return 0;
}