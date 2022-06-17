#include <bus/i2c.hpp>
#include <pico/stdlib.h>
#include <pico/binary_info.h>
#include <hardware/i2c.h>

namespace bus
{
    I2c::I2c(i2c_inst_t *i2c, uint baudrate, uint sda_gpio, uint scl_gpio) : i2c(i2c)
    {
        i2c_init(i2c, baudrate);
        gpio_set_function(sda_gpio, GPIO_FUNC_I2C);
        gpio_set_function(scl_gpio, GPIO_FUNC_I2C);
        gpio_pull_up(sda_gpio);
        gpio_pull_up(scl_gpio);
        bi_decl(bi_2pins_with_func(sda_gpio, scl_gpio, GPIO_FUNC_I2C));
    }

    i2c_inst_t * I2c::get_instance() const
    {
        return i2c;
    }
}
