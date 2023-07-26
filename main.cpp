#include "mbed.h"
#include <FlashIAP.h>

// flashes data to the flash memory
void FlashData(uint32_t address, uint64_t* data, int numberBytes)
{
    FlashIAP flash;
    flash.init();

    int writeWidth = flash.get_page_size();
    int pageSize = flash.get_sector_size(address);

    // calculate the number of double words we need
    int numberDoubleWords = (numberBytes / writeWidth) + (numberBytes % writeWidth != 0);

    // calculate number of pages
    // page is 4096 bytes
    // therefore to calculate number bytes
    int numberPages = (numberBytes / pageSize) + (numberBytes % pageSize != 0);

    // Erase the number of pages we need to
    flash.erase(address, numberPages * pageSize);

    // Flash with our data
    flash.program(data, address, numberDoubleWords * writeWidth);

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
    char data[] = "Hello From Keil Studio Web!!!";
    int dataLength = sizeof(data);

    FlashData((uint32_t)0x081FF000, (uint64_t*)data, dataLength);

    char* readData = (char*)malloc(sizeof(char) * dataLength);
    ReadData((uint32_t)0x081FF000, (uint64_t*)readData, dataLength);
    printf("Data: %s\r\n", readData);

    while (true) {

    }
}

