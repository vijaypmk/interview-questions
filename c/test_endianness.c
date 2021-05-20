#include <stdio.h>
#include <inttypes.h>
#include <assert.h>


int is_little_endian() {
    uint16_t n = 0x0001;
    if(*(uint8_t*)&n == 1) {
        // printf("Little endian.\n");
        return 1;
    }
    else {
        // printf("Big endian.\n");
        return 0;
    }
}


int swap_endian_16b(uint16_t a) {
    return ((a & 0xFF00) >> 8) | ((a & 0x00FF) << 8);
}


int swap_endian_32b(uint32_t a) {
    return ((((a & 0xFF00) >> 8) | ((a & 0x00FF) << 8)) << 16) | 
        ((((a & 0xFF000000) >> 8) | ((a & 0x00FF0000) << 8)) >> 16);
}


int main(void) {

    assert(is_little_endian() == 1);
    assert(swap_endian_16b(0x3F) == 0x3F00);
    assert(swap_endian_32b(0xAB000013) == 0x130000AB);

    return 0;
}