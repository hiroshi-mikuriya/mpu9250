#define I2C 1
#define SPI 2
#define MODE    I2C

#if MODE == I2C
#include "mpu9250i2c.h"
#else // SPI
#include "mpu9250spi.h"
#endif // MODE
#include <stdio.h>
#include <unistd.h>

int main()
{
#if MODE == I2C
    int err = init_mpu9250(0x68);
    if (err)
        return err;
    for (;;) {
        short accel[3] = { 0 };
        short gyro[3] = { 0 };
        short mag[3] = { 0 };
        err = read_accel(accel);
        if (err)
            return err;
        err = read_gyro(gyro);
        if (err)
            return err;
        err = read_mag(mag);
        if (err)
            return err;
        printf("accel:%7d%7d%7d  gyro:%7d%7d%7d  mag:%7d%7d%7d\n", accel[0], accel[1], accel[2],
               gyro[0], gyro[1], gyro[2], mag[0], mag[1], mag[2]);
        usleep(100 * 1000);
    }
    return 0;
#else // SPI
    int cs = 0;
    int err = mpu9250spi_init(cs);
    if (err)
        return err;
    for (;;) {
        short accel[3] = { 0 };
        short gyro[3] = { 0 };
        err = mpu9250spi_accel(accel);
        if (err)
            return err;
        err = mpu9250spi_gyro(gyro);
        if (err)
            return err;
        printf("accel:%7d%7d%7d  gyro:%7d%7d%7d\n", accel[0], accel[1], accel[2],
               gyro[0], gyro[1], gyro[2]);
        usleep(100 * 1000);
    }
#endif // MODE
}
