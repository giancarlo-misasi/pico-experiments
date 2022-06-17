/**
 * @file button.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief for interpreting button input
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <optional>
typedef unsigned int uint;

namespace devices
{
    class Button
    {
        uint gpio;
        bool pressed;

    public:
        Button(uint gpio);
        bool is_pressed() const;
        std::optional<bool> has_changed() const;
        void update();
    };
}
