#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>

#define QUEUE_SIZE 500

typedef struct {
    int *buffer;
    int head;
    int tail;
    int queue_size;
    int cur_size;
} circ_queue_t;


circ_queue_t* queue_create(int queue_size) {
    circ_queue_t *circ_queue = (circ_queue_t*)malloc(sizeof(circ_queue_t));
    if(!circ_queue)
        return NULL;
    circ_queue->buffer = (int*)malloc(sizeof(int) * queue_size);
    if(!circ_queue->buffer) {
        free(circ_queue);
        return NULL;
    }

    circ_queue->head = -1;
    circ_queue->tail = -1;
    circ_queue->cur_size = 0;
    circ_queue->queue_size = queue_size;

    return circ_queue;
}


void queue_free(circ_queue_t* obj) {
    if (obj) {
        free(obj->buffer);
        free(obj);
    }
}


int queue_full(circ_queue_t *obj) {
    return (int)(obj->cur_size == obj->queue_size);
}


int queue_empty(circ_queue_t *obj) {
    return (int)(obj->cur_size == 0);
}


int queue_resize(circ_queue_t* obj) {
    int *new_buf = (int*)malloc((obj->queue_size * 2) * sizeof(int));
    if (!new_buf)
        return -1;
    
    int j = 0;
    for (int i = obj->head; i <= obj->tail; i++) {
        new_buf[j++] = obj->buffer[i];
    }
    obj->head = 0;
    obj->tail = j - 1;
    int *temp = obj->buffer;
    obj->buffer = new_buf;
    obj->queue_size *= 2;

    free(temp);
}


int queue_push(circ_queue_t *obj, int v) {
    if (queue_full(obj)) {
        return -1;
    }
    obj->tail = (obj->tail + 1) % obj->queue_size;
    obj->buffer[obj->tail] = v;

    obj->cur_size++;

    if (obj->head < 0)
        obj->head = 0;

    return 0;
}

int queue_pop(circ_queue_t *obj) {
    if(queue_empty(obj)) {
        return -1;
    }

    obj->head = (obj->head + 1) % obj->queue_size;
    obj->cur_size--;

    return 0;
}


int queue_front(circ_queue_t *obj) {
    if(queue_empty(obj))
        return -1;
    return obj->buffer[obj->head];
}

int queue_rear(circ_queue_t *obj) {
    if(queue_empty(obj))
        return -1;
    return obj->buffer[obj->tail];
}


int main(void) {
    circ_queue_t *obj = queue_create(10);
    if(!obj)
        return -1;

    assert(queue_push(obj, 1) == 0);
    assert(queue_push(obj, 2) == 0);
    assert(queue_front(obj) == 1);
    assert(queue_rear(obj) == 2);
    assert(queue_pop(obj) == 0);
    assert(queue_front(obj) == 2);
    assert(queue_rear(obj) == 2);
    assert(queue_pop(obj) == 0);
    assert(queue_front(obj) == -1);
    assert(queue_rear(obj) == -1);

    for(int i = 0; i < 10; i++) {
        assert(queue_push(obj, i) == 0);
    }

    assert(queue_push(obj, 10) == -1);
    assert(queue_front(obj) == 0);
    assert(queue_rear(obj) == 9);

    queue_free(obj);
    return 0;
}