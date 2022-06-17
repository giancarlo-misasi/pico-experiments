/**
 * @file i2c.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief for interacting with the i2c bus on the pico
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

struct i2c_inst;
typedef i2c_inst i2c_inst_t;
typedef unsigned int uint;

namespace bus
{
    class I2c
    {
        i2c_inst_t *i2c;

    public:
        I2c(i2c_inst_t *i2c, uint baudrate, uint sda_gpio, uint scl_gpio);
        i2c_inst_t * get_instance() const;
    };
}
