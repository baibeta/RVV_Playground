#include <riscv_vector.h>
#include <stdio.h>
#include "utils.c"


int main() {
    /**
    * Reinterpret Cast Conversion Functions: 216 intrinsics
    * Vector LMUL Extension Functions: 135 intrinsics
    * Vector Initialization Functions: 59 intrinsics
    * Vector Insertion Functions: 66 intrinsics
    * Vector Extraction Functions: 66 intrinsics
    */

    // Reinterpret Cast Conversion Functions: 216 intrinsics
    // Reinterpret between different type under the same SEW/LMUL
    size_t vl = vsetvlmax_e32m1();
    vuint32m1_t u32vector = vid_v_u32m1(vl);
    vint32m1_t i32vector = vreinterpret_v_u32m1_i32m1 (u32vector);
    dump_i32_vector(i32vector, vl);


    float f[4] = {0.1, 0.2, 0.3, 0.4};
    vfloat32m1_t f_vector = vle32_v_f32m1(f, vl);
    vint32m1_t if32vector = vreinterpret_v_f32m1_i32m1 (f_vector);
    dump_i32_vector_hex(if32vector, vl);


    // Vector LMUL Extension Functions
    // m1 -> m2 m4 m8
    // Vector LMUL Truncation Functions
    // m8 m4 m2 -> m1
    // ERROR IN THEAD:
  //  __int64_t l[2] = {1,2};
  //  vint64m1_t i64vector = vle64_v_i64m1(l, vl);
  //  vint64m2_t i64vector_mul2 = vlmul_ext_v_i64m1_i64m2(i64vector);
  //  vfloat32mf2_t f64vector_mf2 = vlmul_trunc_v_f32m1_f32mf2(f_vector);


    // Vector Insertion Functions:
    // [0.100000] [0.200000] [0.300000] [0.400000] 
    dump_f32m1_vector(f_vector, vl);
    vfloat32m2_t dest = vundefined_f32m2 ();
    // [0.000000] [0.000000] [0.000000] [0.000000] [0.100000] [0.200000] [0.300000] [0.400000] 
    dest = vset_v_f32m1_f32m2(dest, 1, f_vector);
    dump_f32m2_vector(dest, vl*2);


    // Vector Extraction Functions
    // [0.000000] [0.000000] [0.000000] [0.000000] 
    dump_f32m1_vector(vget_v_f32m2_f32m1(dest,0),vl);
    // [0.100000] [0.200000] [0.300000] [0.400000] 
    dump_f32m1_vector(vget_v_f32m2_f32m1(dest,1),vl);

    return 0;
}