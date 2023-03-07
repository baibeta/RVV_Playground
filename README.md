# RISC-V Vector Extension Intrinsic Playground


# Toolchains
THead gcc&gdb:
>https://occ.t-head.cn/community/download?id=4090445921563774976

THead QEMU:
>https://occ.t-head.cn/community/download?id=4108987827910414336

THead RVV Intrinsic Manual:
>https://occ-oss-prod.oss-cn-hangzhou.aliyuncs.com/resource//1663142200670/Xuantie+900+Series+RVV-1.0+Intrinsic+Manual.pdf

# DEBUG
Run QEMU and pause to debug
```
qemu-riscv64 -cpu c908v -g 1234 rvv_ld_st
```
Run GDB and attach to QEMU
```
riscv64-unknown-linux-gnu-gdb rvv_demo -ex "target remote localhost:1234"
```
eg. print vector register:
```
(gdb) c
Continuing.

Breakpoint 2, main () at rvv_ld_st.c:14
14          printf("b = [%f %f %f %f]\n",b[0],b[1],b[2],b[3]);
(gdb) p/x $v1
$1 = {q = {0x3ecccccd3e99999a3e4ccccd3dcccccd},
      l = {0x3e4ccccd3dcccccd, 0x3ecccccd3e99999a},
      w = {0x3dcccccd, 0x3e4ccccd, 0x3e99999a, 0x3ecccccd},
      s = {0xcccd, 0x3dcc, 0xcccd, 0x3e4c, 0x999a, 0x3e99, 0xcccd, 0x3ecc},
      b = {0xcd, 0xcc, 0xcc, 0x3d, 0xcd, 0xcc, 0x4c, 0x3e, 0x9a, 0x99, 0x99, 0x3e, 0xcd, 0xcc, 0xcc, 0x3e}}
```

