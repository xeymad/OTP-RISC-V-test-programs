#include "start_uart.h"
#include "string_to_int.h"
#define MSG_SIZE 9

void saveInstruction(unsigned int instruction){
    // Address to store the word
    volatile unsigned int* targetAddress = (volatile unsigned int*)0x800008ac;
    *targetAddress = instruction;
    return;
}

int main(void){
    char input[MSG_SIZE];
    UART_init();
    while(1){
        UART_write_string("Write value: 909ff0ef\r\n");
        UART_read_string(input);
        unsigned int instruction = hexStringToInt(input);
        saveInstruction(instruction);
        UART_write_string("Nice one!\r\n"); // present at 800008ac
        UART_write_string(input);
        UART_write_char('\n');
    }
    return 0;
}