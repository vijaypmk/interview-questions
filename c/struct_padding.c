#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

typedef struct
{
    uint8_t a;
    uint16_t b;
}struct_a;

typedef struct
{
    uint8_t a;
    uint16_t b;
    uint16_t c;
}struct_b;

typedef struct
{
    uint8_t a;
    uint16_t b;
    uint16_t c;
}__attribute__((packed)) struct_c;


int main(void) {
    struct_a a_t;
    assert((int)sizeof(a_t) == 4);

    struct_b b_t;
    assert((int)sizeof(b_t) == 6);

    struct_c c_t;
    assert((int)sizeof(c_t) == 5);

    return 0;
}