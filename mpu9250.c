#include "mpu9250.h"
#include "mpu9250reg.h"
#include "i2c.h"
#include <unistd.h>

static uint8_t s_dev_addr; // slave address of mpu9250 expected 0x68 o r0x69.
#define AK8963_ADDR 0x0C

int init_mpu9250(uint8_t dev_addr)
{
    int res = 0;
#define CHK(err) do { res = err; if (res != 0) goto init_mpu9250_end; } while(0)
    s_dev_addr = dev_addr;
    CHK(i2c_init(s_dev_addr));
    uint8_t v0[] = { REG_INT_PIN_CFG, 0x02 };
    CHK(i2c_write(v0, sizeof(v0)));
    i2c_deinit();

    CHK(i2c_init(AK8963_ADDR));
    uint8_t v1[] = { REG_MAG_CNTL, 0x16 }; // 磁気センサの出力周期(100Hz)
    CHK(i2c_write(v1, sizeof(v1)));
    // TODO: Adjを取得し保持する。
#undef CHK
init_mpu9250_end:
    i2c_deinit();
    return res;
}

int read_accel(short * accel)
{
    int res = 0;
#define CHK(err) do { res = err; if (res != 0) goto read_accel_end; } while(0)
    CHK(i2c_init(s_dev_addr));
    uint8_t v = REG_ACCEL_XOUT_H;
    uint8_t buf[6] = { 0 };
    CHK(i2c_write_read(&v, sizeof(v), buf, sizeof(buf)));
    for (int i = 0; i < 3; ++i) {
        accel[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    }
#undef CHK
read_accel_end:
    i2c_deinit();
    return res;
}

int read_gyro(short * gyro)
{
    int res = 0;
#define CHK(err) do { res = err; if (res != 0) goto read_gyro_end; } while(0)
    CHK(i2c_init(s_dev_addr));
    uint8_t v = REG_GYRO_XOUT_H;
    uint8_t buf[6] = { 0 };
    CHK(i2c_write_read(&v, sizeof(v), buf, sizeof(buf)));
    for (int i = 0; i < 3; ++i) {
        gyro[i] = (short)((buf[i * 2] << 8) + (buf[i * 2 + 1] & 0xFF));
    }
#undef CHK
read_gyro_end:
    i2c_deinit();
    return res;
}

int read_mag(short * mag)
{
    int res = 0;
#define CHK(err) do { res = err; if (res != 0) goto read_mag_end; } while(0)
    CHK(i2c_init(AK8963_ADDR));
    for (uint8_t b = 0;;) {
        uint8_t d = REG_MAG_ST1;
        CHK(i2c_write_read(&d, sizeof(d), &b, sizeof(b)));
        if (b & 0x01)
            break;
        usleep(1000);
    }
    uint8_t buf[7] = { 0 };
    uint8_t d = REG_MAG_HXL;
    CHK(i2c_write_read(&d, sizeof(d), buf, sizeof(buf)));
    for (int i = 0; i < 3; ++i) {
        mag[i] = (short)((buf[i * 2] & 0xFF) + (buf[i * 2 + 1] << 8)); // TODO: use Adj
    }
#undef CHK
read_mag_end:
    i2c_deinit();
    return res;
}
