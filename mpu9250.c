#include "mpu9250.h"
#include "mpu9250reg.h"
#include "i2c.h"

static int write(uint8_t dev_addr, uint8_t * buf, uint16_t len)
{
    int res = i2c_init(dev_addr);
    if (res != 0)
        return res;
    res = i2c_write(buf, len);
    if (res != 0)
        return res;
    return i2c_deinit();
}

static int read(uint8_t dev_addr, uint8_t reg, uint8_t * rbuf, uint16_t rlen)
{
    int res = i2c_init(dev_addr);
    if (res != 0)
        return res;
    res = i2c_read(&reg, sizeof(reg), rbuf, rlen);
    if (res != 0)
        return res;
    return i2c_deinit();
}

static uint8_t s_dev_addr;

int init_mpu9250(uint8_t dev_addr)
{
    s_dev_addr = dev_addr;
    return 0;
}

int read_accel(short * accel)
{
    uint8_t buf[6] = { 0 };
    int res = read(s_dev_addr, REG_ACCEL_XOUT_H, buf, sizeof(buf));
    if (res != 0)
        return res;
    for (int i = 0; i < 3; ++i) {
        accel[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    }
    return 0;
}

int read_gyro(short * gyro)
{
    uint8_t buf[6] = { 0 };
    int res = read(s_dev_addr, REG_GYRO_XOUT_H, buf, sizeof(buf));
    if (res != 0)
        return res;
    for (int i = 0; i < 3; ++i) {
        gyro[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    }
    return 0;
}

int read_mag(short * mag)
{
    return 0;
}
