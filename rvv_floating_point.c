#include <riscv_vector.h>
#include <stdio.h>
#include "utils.c"

int main() {
    size_t vl = vsetvlmax_e32m1();
    float a[4] = {0.1, 0.2, 0.3, 0.4};
    float b[4] = {-0.5, 0.6, 0.7, 0.8};
    vfloat32m1_t v_a = vle32_v_f32m1 (a, vl);
    vfloat32m1_t v_b = vle32_v_f32m1 (b, vl);

    // Vector Single-Width Floating-Point Add/Subtract Functions
    dump_f32m1_vector( vfadd_vv_f32m1 (v_a, v_b, vl), vl);

    // Vector Widening Floating-Point Add/Subtract Functions
    dump_f64m2_vector( vfwadd_vv_f64m2 (v_a, v_b, vl), vl);

    // Vector Single-Width Floating-Point Multiply/Divide Functions
    dump_f32m1_vector( vfmul_vv_f32m1 (v_a, v_b, vl), vl);

    // Vector Widening Floating-Point Multiply
    dump_f64m2_vector( vfwmul_vv_f64m2 (v_a, v_b, vl), vl);

    // Vector Single-Width Floating-Point Fused Multiply-Add
    // overwrites multiplicand
    dump_f32m1_vector( vfmadd_vv_f32m1 (v_a, v_b, v_b, vl), vl);
    // overwrites addend
    dump_f32m1_vector( vfmacc_vv_f32m1 (v_a, v_b, v_b, vl), vl);

    // Vector Widening Floating-Point Fused Multiply-Add
    dump_f64m2_vector( vfwmacc_vv_f64m2 (vfwmul_vv_f64m2 (v_a, v_b, vl), v_a, v_b, vl), vl);

    // Vector Floating-Point Square-Root Functions
    dump_f32m1_vector( vfsqrt_v_f32m1 (v_a, vl), vl);
    // Vector Floating-Point Reciprocal Square-Root Estimate Functions
    dump_f32m1_vector( vfrsqrt7_v_f32m1 (v_a, vl), vl);
    // Vector Floating-Point Reciprocal Estimate Functions
    dump_f32m1_vector( vfrec7_v_f32m1 (v_a, vl), vl);

    // Vector Floating-Point MIN/MAX
    dump_f32m1_vector( vfmin_vv_f32m1 (v_a, v_b, vl), vl);
    dump_f32m1_vector( vfmax_vv_f32m1 (v_a, v_b, vl), vl);

    // Vector Floating-Point Absolute Value 
    dump_f32m1_vector( vfabs_v_f32m1 (v_a, vl), vl);

    // Vector Floating-Point Sign-Injection
    // inject v_b sign-bit to v_a
    dump_f32m1_vector( vfsgnj_vv_f32m1 (v_a, v_b, vl), vl);

    // Vector Floating-Point Compare Functions
    printf("Vector Floating-Point Compare Functions \n");
    dump_vbool32_mask(vmfeq_vv_f32m1_b32 (v_a, v_a, vl), vl);
    dump_vbool32_mask(vmfeq_vv_f32m1_b32 (v_a, v_b, vl), vl);
    dump_vbool32_mask(vmfgt_vv_f32m1_b32 (v_a, v_b, vl), vl);

    // Vector Floating-Point Classify Functions
    printf("Vector Floating-Point Classify Functions \n");
    uint32_t class[4] = {0};
    vuint32m1_t v_class = vfclass_v_u32m1 (v_a, vl);
    vse32_v_u32m1(class, v_class, vl);
    for(int j = 0; j < vl; j++) {
        for(int i = 0; i < 10; i++) {
            printf("%d", (class[j] >> i) & 1);
        }
        printf(" ");
    }
    printf("\n");

    v_class = vfclass_v_u32m1 (v_b, vl);
    vse32_v_u32m1(class, v_class, vl);
    for(int j = 0; j < vl; j++) {
        for(int i = 0; i < 10; i++) {
            printf("%d", (class[j] >> i) & 1);
        }
        printf(" ");
    }
    printf("\n");


    // Vector Floating-Point Merge Functions
    // mask = 1000
    vbool32_t mask = vmfgt_vv_f32m1_b32 (v_a, v_b, vl);
    // mask = 1 copy from vector2, otherwise from vector1
    dump_f32m1_vector( vmerge_vvm_f32m1 (mask, v_a, v_b, vl) , vl);

    // Vector Floating-Point Move Functions
    dump_f32m1_vector( vmv_v_v_f32m1 (v_a, vl) , vl);


    // Single-Width Floating-Point/Integer Type-Convert Functions:
    float ff[4] = {-3.5, 1.6, 2.7, 3.3};
    vfloat32m1_t v_ff = vle32_v_f32m1 (ff, vl);
    // [-4] [2] [3] [3] 
    dump_i32_vector( vfcvt_x_f_v_i32m1 (v_ff, vl) ,vl);

    // Widening Floating-Point/Integer Type-Convert Functions
    // [-4] [2] [3] [3] 
    dump_i64m2_vector( vfwcvt_x_f_v_i64m2 (v_ff, vl) ,vl);

    // Narrowing Floating-Point/Integer Type-Convert Functions
    dump_i16mf2_vector( vfncvt_x_f_w_i16mf2 (v_ff, vl) ,vl);

}