#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "zenoh-pico/system/platform.h"

extern uint32_t ZenohUser_GetRandomU32(void);

/*------------------ Random ------------------*/
uint8_t z_random_u8(void) { return (uint8_t)z_random_u32(); }

uint16_t z_random_u16(void) { return (uint16_t)z_random_u32(); }

uint32_t z_random_u32(void) { return ZenohUser_GetRandomU32(); }

uint64_t z_random_u64(void) {
    uint64_t value = 0;
    value |= (uint64_t)z_random_u32();
    value = value << 32U;
    value |= (uint64_t)z_random_u32();
    return value;
}

void z_random_fill(void *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        *((uint8_t *)buf) = z_random_u8();
    }
}

/*------------------ Memory ------------------*/
/* TODO custom static memory allocator */

void *z_malloc(size_t size) { return malloc(size); }

void *z_realloc(void *ptr, size_t size) { return realloc(ptr, size); }

void z_free(void *ptr) { free(ptr); }