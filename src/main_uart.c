#include "start_uart.h"
#define MSG_SIZE 256

int main(void){
    char input[MSG_SIZE];
    input[0] = '\0';
    UART_init();
    while(input[0] != '0'){
        UART_write_string("Hello World! Write something:\r\n");
        UART_read_string(input);
        UART_write_string("You wrote:\r\n");
        UART_write_string(input);
        UART_write_char('\n');
    }
    return 0;
}