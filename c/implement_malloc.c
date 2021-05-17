#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>

typedef struct {
    size_t size;        // size of current block
    struct block_meta *next;   // pointer to next block
    uint8_t free;       // keep track of block being free or not
}block_meta;

#define META_SIZE sizeof(block_meta)

// header for first block
void *global_base = NULL;

// find a free block from existing list
block_meta *find_free_block(block_meta *last, size_t size) {
    block_meta *current = global_base;
    while (current && !(current->free && current->size >= size)) {
        last = current;
        current = current->next;
    }
    return current;
}

// create a new block
block_meta *request_space(block_meta *last, size_t size) {
    block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    // can talk about how to make this thread safe
    assert((void*)block == request);
    if (request == (void*)-1) {
        // sbrk failed
        return NULL;
    }
    if (last) {
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;

    return block;
}


void *my_malloc(size_t size) {
    printf("Calling malloc.\n");
    block_meta *block;
    // can do alignment here

    if (size <= 0)
        return NULL;
    
    // first ever call
    if(!global_base) {
        block = request_space(NULL, size);
        if (!block)
            return NULL;
        global_base = block;
    }
    else {
        block = find_free_block(global_base, size);
        // no free blocks found
        if (!block) {
            block = request_space(global_base, size);
            if (!block)
                return NULL;
        }
        // free block found
        else {
            block->free = 0;
        }
    }

    // block + 1 so as to return location after block_meta
    return (block + 1);
}

// from pointer get head of the list
block_meta *get_block_ptr(void *ptr) {
    return (block_meta*)ptr - 1;
}

void my_free(void *ptr) {
    printf("Calling free.\n");
    if (!ptr)
        return;
    
    block_meta *block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    block_ptr->free = 1;
}


int main(void) {
    void *p = my_malloc(1);
    *(int*)p = 1;
    printf("Location of p %p with value %d\n", p, *(int*)p);
    my_free(p);
}