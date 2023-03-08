#include <riscv_vector.h>
#include <stdio.h>
#include <inttypes.h>


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
void dump_i32_vector(vint32m1_t v, size_t vl) {
    __int32_t* array = (__int32_t*)malloc(vl * sizeof(__int32_t));
    vse32_v_i32m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%d] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_u32_vector(vuint32m1_t v, size_t vl) {
    uint32_t* array = (uint32_t*)malloc(vl * sizeof(uint32_t));
    vse32_v_u32m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%d] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_i64m2_vector(vint64m2_t v, size_t vl) {
    __int64_t* array = (__int64_t*)malloc(vl * sizeof(__int64_t));
    vse64_v_i64m2(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%"PRId64"] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_i16mf2_vector(vint16mf2_t v, size_t vl) {
    __int16_t* array = (__int16_t*)malloc(vl * sizeof(__int16_t));
    vse16_v_i16mf2(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%"PRId16"] ",array[i]);
    }
    printf("\n");
    free(array);
}
void printBinary(uint8_t c) {
    for(int i = 0; i < 8; i++) {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}


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


    return 0;
}