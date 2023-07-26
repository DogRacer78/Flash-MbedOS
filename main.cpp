#include "mbed.h"
#include <FlashIAP.h>

// flashes data to the flash memory
void FlashData(uint32_t address, uint64_t* data, int numberBytes)
{
    FlashIAP flash;
    flash.init();

    // calculate the number of double words we need
    int numberDoubleWords = (numberBytes / 8) + (numberBytes % 8 != 0);

    // calculate number of pages
    // page is 4096 bytes
    // therefore to calculate number bytes
    int numberPages = (numberBytes / 4096) + (numberBytes % 4096 != 0);

    // Erase the number of pages we need to
    flash.erase(address, numberPages * 4096);

    // Flash with our data
    flash.program(data, address, numberDoubleWords * 8);

    flash.deinit();

}

void ReadData(uint32_t address, uint64_t* buff, int numberBytes)
{
    while (numberBytes > 0)
    {
        *buff = *(uint64_t*)address;
        buff++;
        address += 8;
        numberBytes -= 8;
    }
}


// main() runs in its own thread in the OS
int main()
{
    char data[] = "Hello From Keil Studio!!!";
    int dataLength = sizeof(data);

    FlashData((uint32_t)0x081FF000, (uint64_t*)data, dataLength);

    char* readData = (char*)malloc(sizeof(char) * dataLength);
    ReadData((uint32_t)0x081FF000, (uint64_t*)readData, dataLength);
    printf("Data: %s\r\n", readData);

    while (true) {

    }
}

