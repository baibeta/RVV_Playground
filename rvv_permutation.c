#include <riscv_vector.h>
#include <stdio.h>
#include "utils.c"


int main() {
    /**
    * Integer and Floating-Point Scalar Move Functions: 118 intrinsics
    * Vector Slideup Functions: 118 intrinsics
    * Vector Slidedown Functions: 118 intrinsics
    * Vector Slide1up and Slide1down Functions: 236 intrinsics
    * Vector Register Gather Functions: 350 intrinsics
    * Vector Compress Functions: 59 intrinsics
    */

    // Integer and Floating-Point Scalar Move Functions:
    //   The integer scalar read/write instructions transfer
    //   a single value between a scalar x register and element 0 of a vector register. 
    __int32_t int_array[4] = {1,2,3,4};
    float float_array[4] = {0.3,0.2,0.4,0.5};

    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_int = vle32_v_i32m1 (int_array, vl);
    vfloat32m1_t v_float = vle32_v_f32m1 (float_array, vl);

    printf("%d %f \n", vmv_x_s_i32m1_i32(v_int) , vfmv_f_s_f32m1_f32(v_float));
    vint32m1_t v_int_dst = vundefined_i32m1();
    v_int_dst = vmv_s_x_i32m1(v_int_dst, 3,vl);
    dump_i32_vector(v_int_dst,vl);


    // Vector Slideup/Slidedown Functions
    // vint32m1_t vslideup_vx_i32m1 (vint32m1_t dest, vint32m1_t src, size_t offset, size_t vl);
    // v1 = v1 + v2(slideup offset)
    dump_i32_vector(v_int,vl);
    v_int = vslideup_vx_i32m1(v_int, v_int, 2, vl);
    dump_i32_vector(v_int,vl);
    // v1 = v1 + v2(slidedown offset)
    v_int = vslidedown_vx_i32m1(v_int, v_int, 2, vl);
    dump_i32_vector(v_int,vl);

    // Vector Slide1up and Slide1down Functions
    // vint32m1_t __riscv_vslide1up_vx_i32m1 (vint32m1_t src, int32_t value, size_t vl);
    // v_int = 1 2 0 0
    v_int = vslide1up_vx_i32m1 (v_int, 44, vl);
    dump_i32_vector(v_int,vl);
    // v_int = 44 1 2 0
    v_int = vslide1down_vx_i32m1 (v_int, 44, vl);
    // v_int = 1 2 0 44
    dump_i32_vector(v_int,vl);


    // Vector Register Gather Functions:
    __int32_t ia[4] = {5,6,7,8};
    vint32m1_t v_a = vle32_v_i32m1 (ia, vl);
    // [5] [5] [5] [5] 
    // [6] [6] [6] [6] 
    // [7] [7] [7] [7] 
    // [8] [8] [8] [8] 
    dump_i32_vector(vrgather_vx_i32m1(v_a,0,vl), vl);
    dump_i32_vector(vrgather_vx_i32m1(v_a,1,vl), vl);
    dump_i32_vector(vrgather_vx_i32m1(v_a,2,vl), vl);
    dump_i32_vector(vrgather_vx_i32m1(v_a,3,vl), vl);

    __uint32_t i_index[4] = {2,1,3,0};
    vuint32m1_t v_index = vle32_v_u32m1 (i_index, vl);
    // [7] [6] [8] [5] 
    dump_i32_vector(vrgather_vv_i32m1(v_a,v_index,vl), vl);

    // Vector Compress Functions:
    // The vector compress instruction allows elements selected by a vector
    // mask register from a source vector register group to be packed 
    // into contiguous elements at the start of the destination vector register group.

    // mask = 11010010
    // src  = 87654321
    // dst  = 00000000
    // ---- compress --
    // dst  = 87520000
    uint8_t mask[1] = {75};
    vbool8_t v_mask = vlm_v_b8(mask, vl);

    uint8_t src[8] = {8,7,6,5,4,3,2,1};
    uint8_t dst[8] = {0};
    vuint8m1_t v_src = vle8_v_u8m1(src, 8);
    vuint8m1_t v_dst = vle8_v_u8m1(dst, 8);

    v_dst = vcompress_vm_u8m1 (v_mask, v_dst, v_src, 8);
    dump_u8_vector(v_dst,8);


    return 0;
}