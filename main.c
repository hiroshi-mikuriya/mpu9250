#include "mpu9250.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    int res = init_mpu9250(0x68);
    if (res != 0)
        return 1;
    for (;;) {
        short accel[3] = { 0 };
        short gyro[3] = { 0 };
        short mag[3] = { 0 };
        if (read_accel(accel) != 0)
            return 1;
        if (read_gyro(gyro) != 0)
            return 1;
        if (read_mag(mag) != 0)
            return 1;
        printf("accel:%7d%7d%7d  gyro:%7d%7d%7d  mag:%7d%7d%7d\n", accel[0], accel[1], accel[2],
               gyro[0], gyro[1], gyro[2], mag[0], mag[1], mag[2]);
        usleep(100 * 1000);
    }
    return 0;
}
