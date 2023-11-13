#include "axi_gpio.h"
#include "axi_uart.h"
#include "int_to_string.h"

int main(void);

// Global Variable to write exceptions
#define EXSTR_SIZE      11
char exstr[EXSTR_SIZE];

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

unsigned int get_mcause(void){
    unsigned int result;
    asm volatile ("csrr %0, mcause" : "=r" (result));
    return result;
}

// Function to get mepc register value
unsigned int get_mepc(void) {
    unsigned int result;
    asm volatile ("csrr %0, mepc" : "=r" (result));
    return result;
}

// Function to get mtval register value
unsigned int get_mtval(void) {
    unsigned int result;
    asm volatile ("csrr %0, mtval" : "=r" (result));
    return result;
}


unsigned int is_exception(unsigned int exno){
    return (exno != 0);
}

unsigned int is_otp_fetch_error_exception(unsigned int exno){
    return (exno == 24);
}

void _exit_loop(void){
    unsigned int mcause = get_mcause();
    if(is_exception(mcause)){
        unsigned int mepc = get_mepc();
        unsigned int mtval = get_mtval();
        // mcause string
        UART_write_string("\r\nException called with mcause ");
        int_to_string(mcause, exstr);
        UART_write_string(exstr);
        // mepc string
        UART_write_string("\r\nmepc: ");
        int_to_hex_string(mepc, exstr, EXSTR_SIZE);
        UART_write_string(exstr);
        // mtval string
        UART_write_string("\r\nmtval: ");
        int_to_hex_string(mtval, exstr, EXSTR_SIZE);
        UART_write_string(exstr);
        UART_write_char('\n');
        // Activate only red led if OTP exception
        if(is_otp_fetch_error_exception(mcause))
            AXIGPIO_writeData(2);   // Red Led Activation
        else
            AXIGPIO_writeData(3);   // Blue&Red Led Activation
    }
    else
        AXIGPIO_writeData(1);       // Blue Led Activation
    asm volatile ("csrw dscratch0, zero");
    while(1)
        ;
}