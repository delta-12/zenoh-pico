#include <stddef.h>
#include <stdlib.h>

/* TODO custom static memory allocator */

void *z_malloc(size_t size) { return malloc(size); }

void *z_realloc(void *ptr, size_t size) { return realloc(ptr, size); }

void z_free(void *ptr) { free(ptr); }