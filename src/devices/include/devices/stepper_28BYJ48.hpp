/**
 * @file stepper_28BYJ48.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief control a stepper motor, model 28BYJ48 with ULN2003 driver board
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <array>
typedef unsigned int uint;

namespace devices
{
    class Stepper28BYJ48
    {
        std::array<uint, 4> gpios;
        bool halfStep;
        int delay_ms;

    public:
        /**
         * @brief Construct a new Stepper. For halfStep 1ms delay is okay, for fullStep use 10+.
         * 
         * @param gpios 
         * @param halfStep 
         * @param delay_ms 
         */
        Stepper28BYJ48(std::array<uint, 4> gpios, bool halfStep, int delay_ms);
        void set_mode(bool halfStep);
        void set_delay(int delay_ms);
        void set_angle(int angle, bool forward = true);
        void step(int count, bool forward = true);
        void set_pins(int value = 0);
    };
}
