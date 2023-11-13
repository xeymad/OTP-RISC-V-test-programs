int main(void);

__attribute__((section(".start")))
void _start(void) __attribute__((naked));

void _exit_loop(void) __attribute__((naked));

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

void _exit_loop(void){
    asm volatile ("csrw dscratch0, zero");
    while(1)
        ;
}