all: rvv_ld_st run
CROSS_COMPILE ?= /data/home/yifan.bai/thead/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.6.1/bin/riscv64-unknown-linux-gnu-
CC=$(CROSS_COMPILE)gcc
CXXFLAGS= -march=rv64gcv_zfh_xtheadc_xtheadv -mabi=lp64d -static -g -Og

rvv_ld_st: rvv_ld_st.c
	${CC} $^ -o $@ ${CXXFLAGS}

run:
	-/data/home/yifan.bai/thead/xuantie-qemu-x86_64-Ubuntu-18.04-20221104-0752.tar/bin/qemu-riscv64 -cpu c908v rvv_ld_st

clean:
	-rm rvv_ld_st
