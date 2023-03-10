#include <riscv_vector.h>
#include <stdio.h>
#include "utils.c"


int main() {
    /**
    * Vector Mask Load/Store Functions: 14 intrinsics
    * Vector Mask-Register Logical Functions: 84 intrinsics
    * Vector count population in mask Functions: 14 intrinsics
    * Find-first-set mask bit Functions: 14 intrinsics
    * Set-before-first mask bit Functions: 14 intrinsics
    * Set-including-first mask bit Functions: 14 intrinsics
    * Set-only-first mask bit Functions: 14 intrinsics
    * Vector Iota Functions: 44 intrinsics
    * Vector Element Index Functions: 44 intrinsics
    */

    // Vector Mask Load/Store Functions: 14 intrinsics
    size_t vl = vsetvlmax_e8m1();
    // 10101010  10011001
    uint8_t mask_array[2] = {170, 153};
    // vlm.v vd, (rs1)   #  Load byte vector of length ceil(vl/8)
    vbool8_t vmask = vlm_v_b8 (mask_array, vl);

    int8_t array_maskoff[16] = {0};
    vint8m1_t v_maskoff = vle8_v_i8m1(array_maskoff, vl);

    int8_t array[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    //  mask = 10101010  10011001
    //  v_array = [0] [2] [0] [4] [0] [6] [0] [8] [9] [0] [0] [12] [13] [0] [0] [16] 
    vint8m1_t v_array = vle8_v_i8m1_m(vmask, v_maskoff, array, vl);
    dump_i8_vector(v_array, vl);

    // 01010100 01100000
    uint8_t mask_array_2[2] = {84, 96};
    vbool8_t vmask_2 = vlm_v_b8 (mask_array_2, vl);


    // Vector Mask-Register Logical Functions: 84 intrinsics
    //  10101010 10011001
    //or
    //  01010100 01100000
    //  11111110 11111001 = 254 249
    vbool8_t mask_or = vmor_mm_b8 (vmask, vmask_2, vl);
    uint8_t mask_or_array[2] = {0};
    vsm_v_b8(mask_or_array, mask_or, vl);
    // mask1 or mask2 = 254 249
    printf("mask1 or mask2 = %d %d\n",mask_or_array[0], mask_or_array[1]);


    // Vector count population in mask Functions: 14 intrinsics
    //  10101010 10011001      //  01010100 01100000
    // 8 , 5
    printf("%d , %d\n", vcpop_m_b8(vmask, vl) , vcpop_m_b8(vmask_2, vl));


    // Find-first-set mask bit Functions:
    //  10101010 10011001      //  01010100 01100000
    // 1 , 2
    printf("%d , %d\n", vfirst_m_b8(vmask, vl) , vfirst_m_b8(vmask_2, vl));


    // Set-before-first mask bit Functions
    //  vmask_2 = 01010100
    // sbf_mask = 00000011
    vbool8_t sbf_mask = vmsbf_m_b8 (vmask_2, vl);
    uint8_t sbf_mask_array[1] = {0};
    vsm_v_b8(sbf_mask_array, sbf_mask, vl);
    printBinary(sbf_mask_array[0], 8);

    // mask_0   = 00000000
    // sbf_mask = 11111111
    uint8_t mask_0[1] = {0};
    vbool8_t vmask_mask_0 = vlm_v_b8 (mask_0, vl);

    sbf_mask = vmsbf_m_b8 (vmask_mask_0, vl);
    vsm_v_b8(sbf_mask_array, sbf_mask, vl);
    printBinary(sbf_mask_array[0], 8);


    // Set-including-first mask bit Functions:
    //  vmask_2 = 01010100
    // sif_mask = 00000111
    sbf_mask = vmsif_m_b8 (vmask_2, vl);
    vsm_v_b8(sbf_mask_array, sbf_mask, vl);
    printBinary(sbf_mask_array[0], 8);

    // Set-only-first mask bit Functions:
    //  vmask_2 = 01010100
    // sof_mask = 00000100
    sbf_mask = vmsof_m_b8 (vmask_2, vl);
    vsm_v_b8(sbf_mask_array, sbf_mask, vl);
    printBinary(sbf_mask_array[0], 8);


    // Vector Iota Functions:
    // sum of all the bits of elements in the mask register
    // whose index is less than the element
    // vmask =  01010101 10011001
    // viota =  00112233 45556777
    vuint8m1_t v_8 = viota_m_u8m1 (vmask ,vl);
    dump_u8_vector(v_8, vl);

    // vmask_2 = 00101010 00000110
    // viota   = 00011223 33333345
    v_8 = viota_m_u8m1 (vmask_2 ,vl);
    dump_u8_vector(v_8, vl);


    // Vector Element Index Functions:
    // [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10] [11] [12] [13] [14] [15] 
    dump_u8_vector(vid_v_u8m1(vl), vl);

    return 0;
}