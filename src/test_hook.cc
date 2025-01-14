#include <stdlib.h>

int main() {
    void *ptr1 = malloc(4);;
    void *ptr2 = malloc(4 * 1024);
    void *ptr3 = malloc(4 * 1024 * 1024);
    void *ptr4 = malloc(4);
    void *ptr5 = malloc(4 * 1024);
    void *ptr6 = malloc(4 * 1024 * 1024);
    void *ptr7 = malloc(4);
    void *ptr8 = malloc(4 * 1024);
    void *ptr9 = malloc(4 * 1024 * 1024);
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    free(ptr5);
    free(ptr6);
    free(ptr7);
    free(ptr8);
    free(ptr9);
    return 0;
}
