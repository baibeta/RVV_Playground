all: rvv_ld_st rvv_int_arith rvv_fixed_point rvv_floating_point rvv_reduction rvv_mask run
CROSS_COMPILE ?= /data/home/yifan.bai/thead/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.6.1/bin/riscv64-unknown-linux-gnu-
CC=$(CROSS_COMPILE)gcc
CXXFLAGS= -march=rv64gcv_zfh_xtheadc_xtheadv -mabi=lp64d -static -g -Og


rvv_ld_st: rvv_ld_st.c
	${CC} $^ -I ./ -o $@ ${CXXFLAGS}

rvv_int_arith: rvv_int_arith.c
	${CC} $^ -I ./ -o $@ ${CXXFLAGS}

rvv_fixed_point: rvv_fixed_point.c
	${CC} $^ -I ./ -o $@ ${CXXFLAGS}

rvv_floating_point: rvv_floating_point.c
	${CC} $^ -I ./ -o $@ ${CXXFLAGS}

rvv_reduction: rvv_reduction.c
	${CC} $^ -I ./ -o $@ ${CXXFLAGS}

rvv_mask: rvv_mask.c
	${CC} $^ -I ./ -o $@ ${CXXFLAGS}

run:
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_ld_st
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_int_arith
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_fixed_point
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_floating_point
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_reduction
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_mask

clean:
	-rm rvv_ld_st rvv_int_arith rvv_fixed_point rvv_floating_point rvv_reduction rvv_mask
