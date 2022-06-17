/**
 * @file led.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief for turning LEDs on and off
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

typedef unsigned int uint;

namespace devices
{
    class Led
    {
        uint gpio;

    public:
        Led(uint gpio);
        void enable(bool enable);
        void blink(uint blink_ms);
    };
}
