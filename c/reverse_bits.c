#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

uint8_t reverseBits(uint8_t n) {
    uint8_t r = 0;

    for (int i = 7; i >= 4; i--) {
        uint8_t t = ((n >> i) & 0x01) << (7 - i);
        uint8_t b = ((n >> (7 - i)) & 0x01) << i;
        r |= (t | b);
    }

    return r;
}


int main(void) {
    uint8_t n = 0b00001111;

    assert(reverseBits(n) == 0b11110000);
    assert(reverseBits(0b10010101) == 0b10101001);

    return 0;
}