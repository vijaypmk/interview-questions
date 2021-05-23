#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>

#define CHECK_MSEC 10           // timer that runs every 10msec
#define PRESS_COUNT 10          // number of counts required to change inputs

// helper function that changes status of switch every 10 counts
bool get_raw() {
    static int8_t count = 10;
    if(count > 0) {
        count--;
        return true;
    }
    else if(count <= 0 && count > -9) {
        count--;
        // uncomment below to add noise
        // if (count == -5)
        //     return true;
        return false;
    }
    else {
        count = 10;
        return false;
    }
}

bool key_state = false;

// returns true if key changed is consistent for a given count
bool get_status() {
    static int8_t count = 10;
    bool new_state = get_raw();
    if(new_state != key_state) {
        if(--count == 0) {
            key_state = new_state;
            count = 10;
            return true;
        }
    }
    else {
        count = 10;
    }

    return false;
}


void run_10_msec() {
    for(int i = 0; i < 23; i++) {
        if(get_status()) {
            printf("Switch changed.\n");
        }
        usleep(100);
    }
}


int main(void) {
    run_10_msec();

    return 0;
}