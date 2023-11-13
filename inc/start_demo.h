#include "axi_gpio.h"

int main(void);

__attribute__((section(".start")))
void _start(void) __attribute__((naked));

void _exit_loop(void) __attribute__((naked));

// Get Exception Number
unsigned int get_exno();

// Return 1 if input number is an exception, 0 otherwise
unsigned int is_exception(unsigned int exno);

// Return 1 if input number is an otp exception, 0 otherwise
unsigned int is_otp_error_exception(unsigned int exno);

void _start(void){
    // Set up stack pointer
    asm volatile ("lui	sp,0x80010");
    // Set mtvec to point to the exception table
    register void* t0 asm ("t0");
    t0 = &_exit_loop; // Address of _exit_loop
    asm volatile ("csrw mtvec, %0" : : "r" (t0));
    main();
    _exit_loop();
}

unsigned int get_exno(){
    unsigned int mcause;
    asm volatile ("csrr %0, mcause" : "=r" (mcause));
    return mcause;
}


unsigned int is_exception(unsigned int exno){
    return (exno != 0);
}

unsigned int is_otp_fetch_error_exception(unsigned int exno){
    return (exno == 24);
}

void _exit_loop(void){
    unsigned int exno = get_exno();
    if(is_otp_fetch_error_exception(exno))
        AXIGPIO_writeData(2);   // Red Led Activation
    else if(is_exception(exno))
        AXIGPIO_writeData(3);   // Blue&Red Led Activation
    else
        AXIGPIO_writeData(1);   // Blue Led Activation
    asm volatile ("csrw dscratch0, zero");
    while(1)
        ;
}