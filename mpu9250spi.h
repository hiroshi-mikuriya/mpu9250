#pragma once

/**
 * @param [in] dev_addr 0x68 or 0x69
 * @return 0:成功 0以外:失敗
 */
int mpu9250spi_init(int cs);

/**
 * @param [in] dev_addr 0x68 or 0x69
 * @return 0:成功 0以外:失敗
 */
int mpu9250spi_deinit(void);

/**
 * @param [out] accel [3] buffer
 * @return 0:成功 0以外:失敗
 */
int mpu9250spi_accel(short * accel);

/**
 * @param [out] gyro [3] buffer
 * @return 0:成功 0以外:失敗
 */
int mpu9250spi_gyro(short * gyro);
