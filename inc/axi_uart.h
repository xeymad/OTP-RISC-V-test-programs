// Base address of the AXI UART Lite
#define UART_BASE_ADDRESS 0x50000000

// Define the offsets for UART registers
#define UART_RX_OFFSET      0x0
#define UART_TX_OFFSET      0x4
#define UART_STATUS_OFFSET  0x8
#define UART_CTRL_OFFSET    0xC

void UART_init();
void UART_write_char(char c);
char UART_read_char();
void UART_write_string(const char* str);
void UART_read_string(char* buffer);

// Function to clears data FIFOs
void UART_init(){
    // Set the TX and RX FIFO reset bits
    *(volatile unsigned int*)(UART_BASE_ADDRESS + UART_CTRL_OFFSET) = 0x7; 
    // Add a delay to allow the reset to take effect
    for (int i = 0; i < 1000; ++i) {
        asm volatile("nop");
    }
    // Clear the TX and RX FIFO reset bits
    *(volatile unsigned int*)(UART_BASE_ADDRESS + UART_CTRL_OFFSET) = 0x0;
}

// Function to write a character to the UART
void UART_write_char(char c) {
    // Poll the status register to check if the transmitter is ready
    while ((*(volatile unsigned int*)(UART_BASE_ADDRESS + UART_STATUS_OFFSET) & 0x4) == 0);

    // Write the character to the TX register
    *(volatile char*)(UART_BASE_ADDRESS + UART_TX_OFFSET) = c;
}

// Function to read a character from the UART
char UART_read_char() {
    // Poll the status register to check if data is available
    while ((*(volatile unsigned int*)(UART_BASE_ADDRESS + UART_STATUS_OFFSET) & 0x1) == 0);
    // Read the character from the RX register
    char data = *(volatile char*)(UART_BASE_ADDRESS + UART_RX_OFFSET);

    return data;
}

// Function to write a string to the UART
void UART_write_string(const char* str) {
    // Iterate through the string and write each character
    while (*str != '\0') {
        UART_write_char(*str);
        str++;
    }
}

// Function to read a string from the UART
void UART_read_string(char* buffer) {
    int i = 0;
    char c;
    // Read characters until a newline or buffer limit is reached
    do{ 
        c = UART_read_char();
        // Store the character in the buffer
        buffer[i++] = c;
    } while (c!='\r');
    buffer[i] = '\0';
}