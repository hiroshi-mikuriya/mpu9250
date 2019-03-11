#include "mpu9250.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    int res = init_mpu9250(0x68);
    if (res != 0)
        return 1;
    for (;;) {
        short gyro[3] = { 0 };
        short accel[3] = { 0 };
        if (read_accel(accel) != 0)
            return 1;
        if (read_gyro(gyro) != 0)
            return 1;
        printf("%8d%8d%8d%8d%8d%8d\n", accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2]);
        sleep(1);
    }
    return 0;
}
