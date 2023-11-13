# OTP-RISC-V-test-programs
Test programs for my OTP RISC-V thesis.
Each of these programs are designed to be compatible with [biRISCV](https://github.com/ultraembedded/biriscv) project.
The instruction memory starts at 0x80000000 where **_start** function is defined.
Programs with names "rvtests" are retrieved and adapted from [RISC-V Benchmarks Repository](https://github.com/riscv-software-src/riscv-tests/tree/master/benchmarks).
For more informations, send a mail to giuseppe.gambardella.gng@gmail.com.

## Dependencies
* riscv-gnu-toolchain (newlib)
## How to Run
* To compile C programs, run ```make```
* Run ```make clean``` to delete all compilations.
