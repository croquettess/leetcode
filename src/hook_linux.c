#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

typedef void *(*malloc_t)(size_t);
typedef void (*free_t)(void *);

static malloc_t real_malloc = NULL;
static free_t real_free = NULL;

__attribute__((constructor)) void init_hooks(void) {
    real_malloc = (malloc_t)dlsym(RTLD_NEXT, "malloc");
    real_free = (free_t)dlsym(RTLD_NEXT, "free");
    if (!real_malloc || !real_free) {
        char buffer[256];
        int len = snprintf(buffer, sizeof(buffer), "Failed to initialize hooks\n");
        write(STDOUT_FILENO, buffer, len);
        exit(1);
    }
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "Hooks initialized\n");
    write(STDOUT_FILENO, buffer, len);
}

void *malloc(size_t size) {
    real_malloc = (malloc_t)dlsym(RTLD_NEXT, "malloc");
    void *ptr = real_malloc(size);
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "malloc(%zu) = %p\n", size, ptr);
    write(STDOUT_FILENO, buffer, len);
    return ptr;
}

void free(void *ptr) {
    real_free = (free_t)dlsym(RTLD_NEXT, "free");
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "free(%p)\n", ptr);
    write(STDOUT_FILENO, buffer, len);
    real_free(ptr);
}
