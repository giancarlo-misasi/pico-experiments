#include <devices/adc.hpp>
#include <algorithm>
#include <hardware/adc.h>

namespace devices
{
    // Mapping between ADC# and GPIO pin
    const int GPIOs[] = {26, 27, 28, 29};

    Adc::Adc(Adc::Input input) : selected(input), temp_sensor_enabled(false)
    {
        adc_init();
        init(input);
        select(input);
    }

    void Adc::init(Adc::Input input)
    {
        check_throw_already_initialized(input);
        adc_gpio_init(GPIOs[(int)input]);
        inputs.push_back(input);
    }

    void Adc::select(Adc::Input input)
    {
        check_throw_not_initialized(input);
        adc_select_input((int)input);
        selected = input;
    }

    uint16_t Adc::read() const
    {
        check_throw_not_initialized(selected);
        return adc_read();
    }

    void Adc::enable_temp_sensor(bool enable)
    {
        adc_set_temp_sensor_enabled(enable);
        temp_sensor_enabled = enable;
    }

    float Adc::read_temperature(char unit) const
    {
        if (!temp_sensor_enabled)
        {
            throw; // "Forgot to enable the temperature sensor.";
        }
        else if (selected != Adc::Input::ADC_TEMPERATURE)
        {
            throw; // "Forgot to select ADC_TEMPERATURE.";
        }

        const float conversionFactor = 3.3f / (1 << 12);
        float adc = (float)adc_read() * conversionFactor;
        float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

        if (unit == 'C')
        {
            return tempC;
        }
        else if (unit == 'F')
        {
            return tempC * 9 / 5 + 32;
        }

        return -1.0f;
    }

    void Adc::check_throw_not_initialized(Adc::Input input) const
    {
        if (!is_init(input))
        {
            throw; // "Forgot to initialize adc input: " + input; // TODO
        }
    }

    void Adc::check_throw_already_initialized(Adc::Input input) const
    {
        if (is_init(input))
        {
            throw; // "Already initialized adc input: " + input; // TODO
        }
    }

    bool Adc::is_init(Adc::Input input) const
    {
        return std::find(inputs.begin(), inputs.end(), input) != inputs.end();
    }
}
