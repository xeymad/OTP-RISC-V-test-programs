#include "start_demo_zybo.h"

int main()
{
    int i = 0;
    int received_data;
    AXIGPIO_setInputDataDirection();
    while(1){
        received_data = AXIGPIO_readData();
        AXIGPIO2_writeData(!received_data);
        i++;
    }
    return XST_SUCCESS;
}