#include <stdint.h>

#include "zenoh-pico/system/link/serial.h"
#include "zenoh-pico/system/platform.h"
#include "zenoh-pico/utils/logging.h"
#include "zenoh-pico/utils/result.h"

extern z_result_t ZenohUser_OpenSerialFromDevice(_z_sys_net_socket_t *socket, const char *const device,
                                                 const uint32_t baudrate);
extern void ZenohUser_CloseSerial(_z_sys_net_socket_t *socket);
extern size_t ZenohUser_SendSerial(const _z_sys_net_socket_t *const socket, const uint8_t *const data,
                                   const size_t size);

z_result_t _z_open_serial_from_pins(_z_sys_net_socket_t *sock, uint32_t txpin, uint32_t rxpin, uint32_t baudrate) {
    (void)(sock);
    (void)(txpin);
    (void)(rxpin);
    (void)(baudrate);

    _Z_ERROR_LOG(_Z_ERR_GENERIC);

    return _Z_ERR_GENERIC;
}

z_result_t _z_open_serial_from_dev(_z_sys_net_socket_t *sock, char *dev, uint32_t baudrate) {
    return ZenohUser_OpenSerialFromDevice(sock, dev, baudrate);
}

z_result_t _z_listen_serial_from_pins(_z_sys_net_socket_t *sock, uint32_t txpin, uint32_t rxpin, uint32_t baudrate) {
    (void)(sock);
    (void)(txpin);
    (void)(rxpin);
    (void)(baudrate);

    _Z_ERROR_LOG(_Z_ERR_GENERIC);

    return _Z_ERR_GENERIC;
}

z_result_t _z_listen_serial_from_dev(_z_sys_net_socket_t *sock, char *dev, uint32_t baudrate) {
    (void)(sock);
    (void)(dev);
    (void)(baudrate);

    _Z_ERROR_LOG(_Z_ERR_GENERIC);

    return _Z_ERR_GENERIC;
}

void _z_close_serial(_z_sys_net_socket_t *sock) { ZenohUser_CloseSerial(sock); }

size_t _z_read_serial_internal(const _z_sys_net_socket_t sock, uint8_t *header, uint8_t *ptr, size_t len) {
    (void)(sock);
    (void)(header);
    (void)(ptr);
    (void)(len);

    /* TODO */

    _Z_ERROR_LOG(_Z_ERR_GENERIC);

    return SIZE_MAX;
}

size_t _z_send_serial_internal(const _z_sys_net_socket_t sock, uint8_t header, const uint8_t *ptr, size_t len) {
    size_t ret = SIZE_MAX;
    uint8_t *tmp_buf = (uint8_t *)z_malloc(_Z_SERIAL_MFS_SIZE);
    uint8_t *raw_buf = (uint8_t *)z_malloc(_Z_SERIAL_MAX_COBS_BUF_SIZE);

    if ((NULL == raw_buf) || (NULL == tmp_buf)) {
        _Z_ERROR("Failed to allocate serial COBS and/or MFS buffer");
    } else {
        size_t ret = _z_serial_msg_serialize(raw_buf, _Z_SERIAL_MAX_COBS_BUF_SIZE, ptr, len, header, tmp_buf,
                                             _Z_SERIAL_MFS_SIZE);

        if (SIZE_MAX == ret) {
        } else if (ret == ZenohUser_SendSerial(&sock, raw_buf, ret)) {
            ret = len;
        } else {
            ret = SIZE_MAX;
        }

        z_free(raw_buf);
        z_free(tmp_buf);
    }

    return ret;
}