#include <devices/button.hpp>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

namespace devices
{
    Button::Button(uint gpio) : gpio(gpio), pressed(false)
    {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_IN);
    }

    bool Button::is_pressed() const
    {
        return gpio_get(gpio) > 0;
    }

    std::optional<bool> Button::has_changed() const
    {
        bool is_currently_pressed = is_pressed();
        if (is_currently_pressed != pressed)
        {
            return {is_currently_pressed};
        }
        return std::nullopt;
    }

    void Button::update()
    {
        pressed = is_pressed();
    }
}
