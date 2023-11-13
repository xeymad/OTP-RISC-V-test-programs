#define XST_FAILURE 1
#define XST_SUCCESS 0
#define AXI_GPIO_BASEADDR 0x40000000
#define AXI_GPIO_TRI1 (AXI_GPIO_BASEADDR+0x4)
#define AXI_GPIO_DATA1 (AXI_GPIO_BASEADDR+0x0)
#define AXI_GPIO2_TRI1 (AXI_GPIO_BASEADDR+0xc)
#define AXI_GPIO2_DATA1 (AXI_GPIO_BASEADDR+0x8)

void AXIGPIO2_writeData(unsigned int data){
    register unsigned int t3 asm ("t3");
    t3 = AXI_GPIO2_DATA1;
    register unsigned int t4 asm ("t4");
    t4 = data;
    asm volatile ("sw t4, 0(t3)");
    return;
}

void AXIGPIO_setInputDataDirection(){
    register unsigned int t3 asm ("t3");
    t3 = AXI_GPIO_BASEADDR;
    register unsigned int t4 asm ("t4");
    t4 = 0xFFFFFFFF;
    asm volatile ("sw t4, 4(t3)");
    return;
}

unsigned int AXIGPIO_readData(){
    register unsigned int t1 asm ("t1");
    t1 = AXI_GPIO_DATA1;
    register unsigned int t2 asm ("t2");
    asm volatile ("lw t2, 0(t1)");
    return t2;
}

void AXIGPIO_writeData(unsigned int data){
    register unsigned int t1 asm ("t1");
    t1 = AXI_GPIO_DATA1;
    register unsigned int t2 asm ("t2");
    t2 = data;
    asm volatile ("sw t2, 0(t1)");
    return;
}