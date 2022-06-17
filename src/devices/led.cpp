#include <devices/led.hpp>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

namespace devices
{
    Led::Led(uint gpio) : gpio(gpio)
    {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
    }

    void Led::enable(bool enable)
    {
        gpio_put(gpio, enable);
    }

    void Led::blink(uint blink_ms)
    {
        enable(true);
        sleep_ms(blink_ms);
        enable(false);
        sleep_ms(blink_ms);
    }
}
