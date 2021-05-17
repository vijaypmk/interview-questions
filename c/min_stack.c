#include <assert.h>
#include <stdio.h>

typedef struct {
    int val;
    int min;
} stack;

#define STACK_SIZE 500
stack st[STACK_SIZE];
int top = -1;

int push(int v) {
    top++;
    if (top == STACK_SIZE) {
        top--;
        return -1;
    }

    st[top].val = v;
    if (top > 0)
        st[top].min = st[top - 1].min <= v ? st[top - 1].min : v;
    else
        st[top].min = v;
    
    return 1;
}

int pop() {
    if (top == -1) {
        return -1;
    }

    return st[top--].val;
}

int min() {
    return st[top].min;
}

int main(void) {
    int a[] = {10, 2, 4, -1, 5};

    for (int i = 0; i < 5; i++) {
        push(a[i]);
    }
    assert(min() == -1);

    assert(pop() == 5);
    assert(pop() == -1);
    assert(min() == 2);

    push(0);
    assert(min() == 0);
    push(-2);
    assert(min() == -2);
    push(0);
    assert(min() == -2);
    assert(pop() == 0);
    assert(pop() == -2);
    assert(min() == 0);
    
    return 0;
}