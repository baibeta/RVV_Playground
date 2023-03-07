#include <riscv_vector.h>
#include <stdio.h>
#include <string.h>


void test_strided() {
    printf("Test strided load and store. \n");
    // load stride = 1 dst = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16]
    // load stride = 2 dst = [1 3 5 7 9 11 13 15]
    // load stride = 4 dst = [1 5 9 13]
    // store stride = 1 dst = [1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16]
    // store stride = 2 dst = [1 0 2 0 3 0 4 0 5 0 6 0 7 0 8 0]
    // store stride = 4 dst = [1 0 0 0 2 0 0 0 3 0 0 0 4 0 0 0]
    int8_t src[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int8_t dst[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    ptrdiff_t stride = 1 * sizeof(int8_t);
    vint8m1_t v_i8 = vlse8_v_i8m1(src, stride, 16);
    vse8_v_i8m1(dst, v_i8, 16);
    printf("load stride = 1 dst = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],
                    dst[4],dst[5],dst[6],dst[7],
                    dst[8],dst[9],dst[10],dst[11],
                    dst[12],dst[13],dst[14],dst[15]);

    stride = 2 * sizeof(int8_t);
    v_i8 = vlse8_v_i8m1(src, stride, 8);
    vse8_v_i8m1(dst, v_i8, 8);
    printf("load stride = 2 dst = [%d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],dst[4],dst[5],dst[6],dst[7]);

    stride = 4 * sizeof(int8_t);
    v_i8 = vlse8_v_i8m1(src, stride, 4);
    vse8_v_i8m1(dst, v_i8, 4);
    printf("load stride = 4 dst = [%d %d %d %d]\n",dst[0],dst[1],dst[2],dst[3]);


    stride = 1 * sizeof(int8_t);
    v_i8 = vle8_v_i8m1(src, 16);
    vsse8_v_i8m1(dst, stride, v_i8, 16);
    printf("store stride = 1 dst = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],
                    dst[4],dst[5],dst[6],dst[7],
                    dst[8],dst[9],dst[10],dst[11],
                    dst[12],dst[13],dst[14],dst[15]);

    stride = 2 * sizeof(int8_t);
    memset(dst, 0, sizeof(dst));
    vsse8_v_i8m1(dst, stride, v_i8, 8);
    printf("store stride = 2 dst = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],
                    dst[4],dst[5],dst[6],dst[7],
                    dst[8],dst[9],dst[10],dst[11],
                    dst[12],dst[13],dst[14],dst[15]);

    stride = 4 * sizeof(int8_t);
    memset(dst, 0, sizeof(dst));
    vsse8_v_i8m1(dst, stride, v_i8, 4);
    printf("store stride = 4 dst = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],
                    dst[4],dst[5],dst[6],dst[7],
                    dst[8],dst[9],dst[10],dst[11],
                    dst[12],dst[13],dst[14],dst[15]);
}



void test_indexed() {
    printf("Test indexed load and store. \n");
    int8_t src[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int8_t dst[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int8_t index[] = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};

    vuint8m1_t bindex = vle8_v_u8m1(index, 16);
    vint8m1_t v_dst = vloxei8_v_i8m1(src, bindex, 16);

    vse8_v_i8m1(dst, v_dst, 16);
    // indexed load dst = [2 3 4 5 2 3 4 5 2 3 4 5 2 3 4 5]
    printf("indexed load dst = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],
                    dst[4],dst[5],dst[6],dst[7],
                    dst[8],dst[9],dst[10],dst[11],
                    dst[12],dst[13],dst[14],dst[15]);

    memset(dst, 0, sizeof(dst));
    v_dst = vluxei8_v_i8m1(src, bindex, 16);
    vse8_v_i8m1(dst, v_dst, 16);
    // indexed load dst = [2 3 4 5 2 3 4 5 2 3 4 5 2 3 4 5]
    printf("indexed load dst = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
                    dst[0],dst[1],dst[2],dst[3],
                    dst[4],dst[5],dst[6],dst[7],
                    dst[8],dst[9],dst[10],dst[11],
                    dst[12],dst[13],dst[14],dst[15]);
}

// reference:
// https://github.com/riscv-non-isa/rvv-intrinsic-doc/blob/master/examples/rvv_strlen.c
size_t strlen_vec(char *src) {
  size_t vlmax = vsetvlmax_e8m8();
  char *copy_src = src;
  long first_set_bit = -1;
  size_t vl;
  while (first_set_bit < 0) {
    vint8m8_t vec_src = vle8ff_v_i8m8(copy_src, &vl, vlmax);
    vbool1_t string_terminate = vmseq_vx_i8m8_b1(vec_src, 0, vl);

    copy_src += vl;

    first_set_bit = vfirst_m_b1(string_terminate, vl);
  }
  copy_src -= vl - first_set_bit;

  return (size_t)(copy_src - src);
}

void test_fault_only_first() {
    printf("Test fault only first load.\n");

    char s0[] = "shfjasjdlfkjaskfdjsl";

    // compute
    size_t golden, actual;
    golden = strlen(s0);
    actual = strlen_vec(s0);

    printf("golden = %d  actual = %d \n", golden, actual);
}


void test_segment() {
    printf("Test segment load and store function.\n");
    float a[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    vfloat32m1_t v0, v1;
    vlseg2e32_v_f32m1(&v0, &v1, a, 4);

    float dst1[4] = {0};
    float dst2[4] = {0};
    vse32_v_f32m1(dst1, v0, 4);
    vse32_v_f32m1(dst2, v1, 4);

    // dst1 = [0.100000 0.300000 0.500000 0.700000]
    // dst2 = [0.200000 0.400000 0.600000 0.800000]
    printf("dst1 = [%f %f %f %f]\n",dst1[0],dst1[1],dst1[2],dst1[3]);
    printf("dst2 = [%f %f %f %f]\n",dst2[0],dst2[1],dst2[2],dst2[3]);

}


int main() {
    float a[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    float b[] = {0, 0, 0, 0};

    printf("Test basic load and store function.\n");
    vfloat32m1_t v_a;
    v_a = vle32_v_f32m1 (a, 4);
    vse32_v_f32m1(b, v_a, 2);
    // b = [0.100000 0.200000 0.000000 0.000000]
    printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);


    printf("Test load and store function with LMUL.\n");
    vfloat32mf2_t v_aa;
    // mf2 means LMUL = 1/2
    // max vl = vlen * lmul / sew = 128 * 0.5 / 32 = 2
    // so v_aa = [0.1, 0.2]
    v_aa = vle32_v_f32mf2 (a, 4);
    vse32_v_f32mf2(b, v_aa, 4);
    // b = [0.100000 0.200000 0.000000 0.000000]
    printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);


    printf("Test VL.\n");
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


    printf("Test load function with Mask.\n");
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


    test_strided();

    test_indexed();

    test_fault_only_first();

    test_segment();

    printf("Finish.\n");

    return 0;
}
