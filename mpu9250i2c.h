#pragma once

#include <stdint.h>

/**
 * @param [in] dev_addr 0x68 or 0x69
 * @return 0:成功 0以外:失敗
 */
int init_mpu9250(uint8_t dev_addr);

/**
 * @param [out] accel [3] buffer
 * @return 0:成功 0以外:失敗
 */
int read_accel(short * accel);

/**
 * @param [out] gyro [3] buffer
 * @return 0:成功 0以外:失敗
 */
int read_gyro(short * gyro);

/**
 * @param [out] mag [3] buffer
 * @return 0:成功 0以外:失敗
 */
int read_mag(short * mag);

