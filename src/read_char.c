#include "start_demo.h"
#include "axi_uart.h"

int main(void){
    char input;
    do {
        input = UART_read_char();
        UART_write_string("OK!\r\n");
    } while(input != '0');
    return 0;
}