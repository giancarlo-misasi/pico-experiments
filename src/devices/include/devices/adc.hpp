/**
 * @file adc.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief for interacting with the adc bus on the pico
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <cstdint>
#include <vector>
typedef unsigned int uint;

namespace devices
{
    class Adc
    {
    public:
        enum Input
        {
            ADC_0 = 0,
            ADC_1,
            ADC_2,
            ADC_VREF,
            ADC_TEMPERATURE
        };

    private:
        std::vector<Adc::Input> inputs;
        Adc::Input selected;
        bool temp_sensor_enabled;

    public:
        Adc(Adc::Input input);
        void init(Adc::Input input);
        void select(Adc::Input input);
        uint16_t read() const;
        void enable_temp_sensor(bool enable);
        float read_temperature(char unit) const;
    private:
        void check_throw_not_initialized(Adc::Input input) const;
        void check_throw_already_initialized(Adc::Input input) const;
        bool is_init(Adc::Input input) const;
    };
}
