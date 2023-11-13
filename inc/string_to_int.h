/**
 * Given a string formatted with hexadecimal numbers,
 * returns the currespundant unsigned int value.
*/
unsigned int hexStringToInt(const char* hexString);

unsigned int hexStringToInt(const char* hexString) {
    unsigned int result = 0;

    for (int i = 0; i < 8; i++) {
        char currentChar = hexString[i];

        // Convert ASCII character to integer value
        int digit;
        if (currentChar >= '0' && currentChar <= '9') {
            digit = currentChar - '0';
        } else if (currentChar >= 'a' && currentChar <= 'f') {
            digit = 10 + (currentChar - 'a');
        } else if (currentChar >= 'A' && currentChar <= 'F') {
            digit = 10 + (currentChar - 'A');
        } else {
            // Handle invalid character
            // You might want to add error handling based on your requirements
            return 0;
        }

        // Shift the existing bits left by 4 and add the new digit
        result = (result << 4) | digit;
    }

    return result;
}