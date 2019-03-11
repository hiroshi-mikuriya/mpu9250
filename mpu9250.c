#include "mpu9250.h"
#include "mpu9250reg.h"
#include "i2c.h"
#include <unistd.h>

static uint8_t s_dev_addr;
#define AK8963_ADDR 0x0C

int init_mpu9250(uint8_t dev_addr)
{
    int res = 0;
    s_dev_addr = dev_addr;
    res = i2c_init(s_dev_addr);
    if (res != 0)
        goto init_mpu9250_end;
    uint8_t v0[] = { REG_INT_PIN_CFG, 0x02 };
    res = i2c_write(v0, sizeof(v0));
    if (res != 0)
        goto init_mpu9250_end;
    i2c_deinit();

    res = i2c_init(AK8963_ADDR);
    if (res != 0)
        goto init_mpu9250_end;
    uint8_t v1[] = { REG_MAG_CNTL, 0x16 };
    res = i2c_write(v1, sizeof(v1));
    if (res != 0)
        goto init_mpu9250_end;
init_mpu9250_end:
    i2c_deinit();
    return res;
}

int read_accel(short * accel)
{
    int res = 0;
    res = i2c_init(s_dev_addr);
    if (res != 0)
        goto read_accel_end;
    uint8_t v = REG_ACCEL_XOUT_H;
    uint8_t buf[6] = { 0 };
    res = i2c_read(&v, sizeof(v), buf, sizeof(buf));
    if (res != 0)
        goto read_accel_end;
    for (int i = 0; i < 3; ++i) {
        accel[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    }
read_accel_end:
    i2c_deinit();
    return res;
}

int read_gyro(short * gyro)
{
    int res = 0;
    res = i2c_init(s_dev_addr);
    if (res != 0)
        goto read_gyro_end;
    uint8_t v = REG_GYRO_XOUT_H;
    uint8_t buf[6] = { 0 };
    res = i2c_read(&v, sizeof(v), buf, sizeof(buf));
    if (res != 0)
        goto read_gyro_end;
    for (int i = 0; i < 3; ++i) {
        gyro[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    }
read_gyro_end:
    i2c_deinit();
    return res;
}

int read_mag(short * mag)
{
    int res = 0;
    res = i2c_init(AK8963_ADDR);
    if (res != 0)
        goto read_mag_end;
    for (uint8_t b = 0;;) {
        uint8_t d = REG_MAG_ST1;
        res = i2c_read(&d, sizeof(d), &b, sizeof(b));
        if (res != 0)
            goto read_mag_end;
        if (b & 0x01)
            break;
        usleep(1000);
    }
    uint8_t buf[7] = { 0 };
    uint8_t d = REG_MAG_HXL;
    res = i2c_read(&d, sizeof(d), buf, sizeof(buf));
    if (res != 0)
        goto read_mag_end;
    for (int i = 0; i < 3; ++i) {
        mag[i] = (short)((buf[i * 2] & 0xFF) + (buf[i * 2 + 1] << 8));
    }
read_mag_end:
    i2c_deinit();
    return res;
}
