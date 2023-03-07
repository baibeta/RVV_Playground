#include <riscv_vector.h>
#include <stdio.h>

int main() {
    float a[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    float b[] = {0, 0, 0, 0};

    printf("Test basic load and store function.");
    vfloat32m1_t v_a;
    v_a = vle32_v_f32m1 (a, 4);
    vse32_v_f32m1(b, v_a, 2);
    // b = [0.100000 0.200000 0.000000 0.000000]
    printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);


    printf("Test load and store function with LMUL.");
    vfloat32mf2_t v_aa;
    // mf2 means LMUL = 1/2
    // max vl = vlen * lmul / sew = 128 * 0.5 / 32 = 2
    // so v_aa = [0.1, 0.2]
    v_aa = vle32_v_f32mf2 (a, 4);
    vse32_v_f32mf2(b, v_aa, 4);
    // b = [0.100000 0.200000 0.000000 0.000000]
    printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);


    printf("Test VL.");
    // check vl
    size_t vlmax = vsetvlmax_e32mf2();
    printf("lmul = 1/2, vlmax = %d \n",vlmax);
    // vlmax = 2
    // vl <= vlmax && vl <= avl
    size_t vl = vsetvl_e32mf2(4);
    printf("lmul = 1/2, avl = 4, vl = %d \n",vl);
    // avl = 1
    vl = vsetvl_e32mf2(1);
    printf("lmul = 1/2, avl = 1, vl = %d \n",vl);


    printf("Test load function with Mask.");
    // vbooln_t => (n = SEW/LMUL = 32/1 = 32) => vbool32_t
    vbool32_t _mask;
    // Vector Floating-Point Less Than
    // v_a = [0.1 0.2 0.3 0.4]
    // _mask => |v_a < 0.4| => _mask = [1 1 1 0]
    float mask_threshold = 0.4f;
    _mask = vmflt_vf_f32m1_b32(v_a, mask_threshold, 4);
    // maskedoff = c
    float c[] = {-0.1, -0.2, -0.3, -0.4};
    vfloat32m1_t masked_v_a, v_maskedoff;
    v_maskedoff = vle32_v_f32m1(c, 4);
    // masked_v_a = a[0] a[1] a[2] c[3]
    masked_v_a = vle32_v_f32m1_m(_mask, v_maskedoff, a, 4);
    vse32_v_f32m1(b, masked_v_a, 4);
    // b = [0.100000 0.200000 0.300000 -0.400000]
    printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);

    return 0;
}
