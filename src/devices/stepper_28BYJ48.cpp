#include <devices/stepper_28BYJ48.hpp>
#include <vector>
#include <pico/stdlib.h>
#include <hardware/gpio.h>

namespace devices
{
    const int A = 0b1000;
    const int B = 0b0100;
    const int C = 0b0010;
    const int D = 0b0001;
    const std::vector<int> HALF_STEPS = {{A, A | B, B, B | C, C, C | D, D, D | A}};
    const std::vector<int> FULL_STEPS = {{A, B, C, D}};
    const float STEPS_PER_DEGREE = 512.0 / 360.0; // Supposed to be 4096 steps per rotation / 8 half steps = 512 (online says 509)

    Stepper28BYJ48::Stepper28BYJ48(std::array<uint, 4> gpios, bool halfStep, int delay_ms)
        : gpios(std::move(gpios)), halfStep(halfStep), delay_ms(delay_ms)
    {
        for (auto gpio : gpios)
        {
            gpio_init(gpio);
            gpio_set_dir(gpio, GPIO_OUT);
            gpio_put(gpio, 0);
        }
    }

    void Stepper28BYJ48::set_mode(bool halfStep)
    {
        this->halfStep = halfStep;
    }

    void Stepper28BYJ48::set_delay(int delay_ms)
    {
        this->delay_ms = delay_ms;
    }

    void Stepper28BYJ48::set_angle(int angle, bool forward)
    {
        step(angle * STEPS_PER_DEGREE, forward);
    }

    void Stepper28BYJ48::step(int count, bool forward)
    {
        for (int i = 0; i < count; ++i)
        {
            const auto &steps = halfStep ? HALF_STEPS : FULL_STEPS;
            if (forward)
            {
                for (auto value : steps)
                {
                    set_pins(value);
                    sleep_ms(delay_ms);
                }
            }
            else
            {
                for (auto it = steps.rbegin(); it != steps.rend(); ++it)
                {
                    set_pins(*it);
                    sleep_ms(delay_ms);
                }
            }
        }
        set_pins(0); // if left on, this causes noise on the power rail, affecting things like adc
    }

    void Stepper28BYJ48::set_pins(int value)
    {
        for (int gpio_idx = 0; gpio_idx < 4; ++gpio_idx)
        {
            gpio_put(gpios[gpio_idx], !!(value & (1 << (4 - gpio_idx - 1))));
        }
    }
}
