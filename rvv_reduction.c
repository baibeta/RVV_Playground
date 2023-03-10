#include <riscv_vector.h>
#include <stdio.h>
#include "utils.c"


int main() {
    /**
    * Vector Single-Width Integer Reduction Functions: 528 intrinsics
    * Vector Widening Integer Reduction Functions: 72 intrinsics
    * Vector Single-Width Floating-Point Reduction Functions: 120 intrinsics
    * Vector Widening Floating-Point Reduction Functions: 44 intrinsics
    */

   // reduction operation includes:
   // sum, max, min
   // and, or, xor

    __int32_t a[] = {1,2,3,4};
    __int32_t b[] = {8,7,6,5};
    size_t vl = vsetvlmax_e32m1();
    vint32m1_t v_a = vle32_v_i32m1 (a, vl);
    vint32m1_t v_b = vle32_v_i32m1 (b, vl);


    // v_dst[0] = sum( v_b[0] , v_a[0 1 2 ...] )
    vint32m1_t v_dst = vundefined_i32m1();
    v_dst = vredsum_vs_i32m1_i32m1 (v_dst, v_a, v_b, vl);
    dump_i32_vector(v_dst,1);

    // v_dst[0] = max( v_b[0] , v_a[0 1 2 ...] )
    v_dst = vredmax_vs_i32m1_i32m1 (v_dst, v_a, v_b, vl);
    dump_i32_vector(v_dst,1);

    // v_dst[0] = min( v_b[0] , v_a[0 1 2 ...] )
    v_dst = vredmin_vs_i32m1_i32m1 (v_dst, v_a, v_b, vl);
    dump_i32_vector(v_dst,1);

    // v_dst[0] = and( v_b[0] , v_a[0 1 2 ...] )
    v_dst = vredand_vs_i32m1_i32m1 (v_dst, v_a, v_b, vl);
    dump_i32_vector(v_dst,1);

    // v_dst[0] = or( v_b[0] , v_a[0 1 2 ...] )
    v_dst = vredor_vs_i32m1_i32m1 (v_dst, v_a, v_b, vl);
    dump_i32_vector(v_dst,1);

    // v_dst[0] = xor( v_b[0] , v_a[0 1 2 ...] )
    v_dst = vredxor_vs_i32m1_i32m1 (v_dst, v_a, v_b, vl);
    dump_i32_vector(v_dst,1);


    // Vector Widening Integer Reduction Instructions
    // only reduce_sum
    // vint64m1_t vwredsum_vs_i32m1_i64m1 (vint64m1_t dest, vint32m1_t vector,
    //                                         vint64m1_t scalar, size_t vl);



    return 0;
}