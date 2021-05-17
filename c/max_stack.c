#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct {
    int val;
    int max;
} MaxStack;

/** initialize your data structure here. */
#define STACK_SIZE 5000
int top = -1;

MaxStack* maxStackCreate() {
    top = -1;
    MaxStack* st = (MaxStack*)malloc(STACK_SIZE*sizeof(MaxStack));
    
    return st;
}

void maxStackPush(MaxStack* obj, int x) {
    top++;
    obj[top].val = x;
    if (top > 0)
        obj[top].max = obj[top - 1].max >= x ? obj[top - 1].max : x;
    else
        obj[top].max = x;
}

int maxStackPop(MaxStack* obj) {
    return obj[top--].val;
}

int maxStackTop(MaxStack* obj) {
    return obj[top].val;
}

int maxStackPeekMax(MaxStack* obj) {
    return obj[top].max;
}

int maxStackPopMax(MaxStack* obj) {
    int m = maxStackPeekMax(obj);
    int a[STACK_SIZE], i = 0;
    while (top > -1) {
        if (maxStackTop(obj) != m) {
            a[i++] = maxStackPop(obj);
        }
        else
            break;
    }
    int n = maxStackPop(obj);
    i--;
    while (i > -1) {
        maxStackPush(obj, a[i--]);
    }
    
    return m;
}

void maxStackFree(MaxStack* obj) {
    free(obj);
}

/**
 * Your MaxStack struct will be instantiated and called as such:
 * MaxStack* obj = maxStackCreate();
 * maxStackPush(obj, x);
 
 * int param_2 = maxStackPop(obj);
 
 * int param_3 = maxStackTop(obj);
 
 * int param_4 = maxStackPeekMax(obj);
 
 * int param_5 = maxStackPopMax(obj);
 
 * maxStackFree(obj);
*/

int main(void) {
    MaxStack *obj = maxStackCreate();
    maxStackPush(obj, 5);
    maxStackPush(obj, 1);
    maxStackPush(obj, 5);

    assert(maxStackTop(obj) == 5);
    assert(maxStackPopMax(obj) == 5);
    assert(maxStackTop(obj) == 1);
    assert(maxStackPeekMax(obj) == 5);
    assert(maxStackPop(obj) == 1);
    assert(maxStackTop(obj) == 5);

    maxStackFree(obj);

    return 0;
}