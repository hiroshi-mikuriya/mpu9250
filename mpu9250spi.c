#include "mpu9250spi.h"
#include "spi.h"
#include "mpu9250reg.h"

static int s_cs = 0;

int mpu9250spi_init(int cs)
{
    s_cs = cs;
    int err = spi_init();
    if (err)
        return err;
    return 0;
}

int mpu9250spi_deinit(void)
{
    return spi_deinit();
}

int mpu9250spi_accel(short * accel)
{
    uint8_t reg = REG_ACCEL_XOUT_H | 0x80;
    uint8_t buf[6] = { 0 };
    int err = spi_write_read(&reg, sizeof(reg), buf, sizeof(buf), s_cs);
    if (err)
        return err;
    for (int i = 0; i < 3; ++i)
        accel[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    return 0;
}

int mpu9250spi_gyro(short * gyro)
{
    uint8_t reg = REG_GYRO_XOUT_H | 0x80;
    uint8_t buf[6] = { 0 };
    int err = spi_write_read(&reg, sizeof(reg), buf, sizeof(buf), s_cs);
    if (err)
        return err;
    for (int i = 0; i < 3; ++i)
        gyro[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    return 0;
}
