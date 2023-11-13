/**
 * int_to_char: converts an integer into a string
*/
void int_to_string(int num, char* buffer);

// Function to convert an integer to a string
void int_to_string(int num, char* buffer) {
    int i = 0;
    int is_negative = 0;

    // Handle the case of a negative number
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Handle the case of zero separately
    if (num == 0) {
        buffer[i++] = '0';
    }

    // Process each digit of the number
    while (num != 0) {
        int digit = num % 10;
        buffer[i++] = digit + '0';
        num = num / 10;
    }

    // Add the negative sign if necessary
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Reverse the string in-place
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    // Add null terminator
    buffer[i] = '\0';
}

// Function to calculate the length of a string
int calculate_string_length(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void int_to_hex_string(int value, char* hex_string, int string_size) {
    // Define the hexadecimal characters
    char hex_chars[] = "0123456789ABCDEF";

    // Ensure that the buffer has enough space
    if (string_size < 2) {
        return; // Insufficient space
    }

    // Null-terminate the string
    hex_string[0] = '\0';

    // Convert each nibble to a hexadecimal character
    for (int i = sizeof(int) * 2 - 1; i >= 0; --i) {
        int nibble = (value >> (i * 4)) & 0xF;
        if (nibble > 0 || hex_string[0] != '\0') {
            // If the current nibble is non-zero or if we've encountered non-zero
            // nibbles before, append the corresponding hex character to the string
            char hex_char = hex_chars[nibble];
            int length = calculate_string_length(hex_string);
            if (length + 1 < string_size) {
                hex_string[length] = hex_char;
                hex_string[length + 1] = '\0';
            } else {
                break; // Insufficient space
            }
        }
    }
}