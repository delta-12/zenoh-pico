#ifndef ZENOH_PICO_SYSTEM_STM32_TYPES_H
#define ZENOH_PICO_SYSTEM_STM32_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t z_clock_t;
typedef uint64_t z_time_t;

typedef struct {
    void *socket;
} _z_sys_net_socket_t;

typedef struct {
    void *endpoint;
} _z_sys_net_endpoint_t;

#ifdef __cplusplus
}
#endif

#endif  // ZENOH_PICO_SYSTEM_STM32_TYPES_H
