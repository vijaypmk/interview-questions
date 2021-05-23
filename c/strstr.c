#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

const char* my_strstr(const char* haystack, const char* needle) {
    int j, k;
    for (int i = 0; haystack[i] != '\0'; i++) {
        j = 0;
        if (haystack[i] == needle[0]) {
            for (k = i; needle[j] != '\0'; k++) {
                if (haystack[k] != needle[j++]) {
                    break;
                }
            }
            if ((k - i) == j)
                return haystack + i;
        }
    }

    return NULL;
}


int main(void) {
    const char *haystack = "Thisdrondroneisawesome.";
    const char *needle = "drone";

    assert(strcmp(my_strstr(haystack, needle), strstr(haystack, needle)) == 0);

    return 0;
}