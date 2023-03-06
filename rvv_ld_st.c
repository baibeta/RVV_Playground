#include <riscv_vector.h>
#include <stdio.h>

int main() {
    float a[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    float b[] = {0, 0, 0, 0};

    vfloat32m1_t v_a;
    v_a = vle32_v_f32m1 (a, 4);

    vse32_v_f32m1(b, v_a, 2);

    // b = [0.100000 0.200000 0.000000 0.000000]
    printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);

    return 0;
}
