#include <riscv_vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void dump_i8_vector(vint8m1_t v, size_t vl) {
    __int8_t* array = (__int8_t*)malloc(vl * sizeof(__int8_t));
    vse8_v_i8m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%"PRId8"] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_u8_vector(vuint8m1_t v, size_t vl) {
    __uint8_t* array = (__uint8_t*)malloc(vl * sizeof(__uint8_t));
    vse8_v_u8m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%"PRId8"] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_i32_vector(vint32m1_t v, size_t vl) {
    __int32_t* array = (__int32_t*)malloc(vl * sizeof(__int32_t));
    vse32_v_i32m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%d] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_i32_vector_hex(vint32m1_t v, size_t vl) {
    __int32_t* array = (__int32_t*)malloc(vl * sizeof(__int32_t));
    vse32_v_i32m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[0x%x] ",array[i]);
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
void dump_f32m1_vector(vfloat32m1_t v, size_t vl) {
    float* array = (float*)malloc(vl * sizeof(float));
    vse32_v_f32m1(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%f] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_f32m2_vector(vfloat32m2_t v, size_t vl) {
    float* array = (float*)malloc(vl * sizeof(float));
    vse32_v_f32m2(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%f] ",array[i]);
    }
    printf("\n");
    free(array);
}
void dump_f64m2_vector(vfloat64m2_t v, size_t vl) {
    double* array = (double*)malloc(vl * sizeof(double));
    vse64_v_f64m2(array, v, vl);
    for(int i = 0; i < vl; i++) {
        printf("[%f] ",array[i]);
    }
    printf("\n");
    free(array);
}

void printBinary(uint8_t c, size_t vl) {
    for(int i = 0; i < vl; i++) {
        printf("%d", (c >> i) & 1);
    }
    printf("\n");
}

void dump_vbool32_mask(vbool32_t vb, size_t vl) {
    uint8_t mask[1] = {0};
    vsm_v_b32 (mask, vb, vl);
    printBinary(mask[0], vl);
}