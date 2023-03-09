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