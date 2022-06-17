/**
 * @file lcd1602.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief for interacting with an 1602 lcd that supports i2c
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <memory>
#include <bus/i2c.hpp>

namespace devices
{
    class Lcd1602
    {
        std::unique_ptr<bus::I2c> i2c;

    public:
        /**
         * @brief Construct and initialize a new Lcd1602 instance to write to
         *
         * @param i2c the output gpio to use
         */
        Lcd1602(std::unique_ptr<bus::I2c> i2c);

        /**
         * @brief Set the cursor position
         *
         * @param line the line (0 or 1)
         * @param position the position in the line (16 per line)
         */
        void set_cursor(int line, int position);

        /**
         * @brief Prints a message to the LCD
         *
         * @param format the message format string
         * @param ... the arguments for the format string
         */
        void printf(const char *format, ...);

        /**
         * @brief Clears the screen
         * 
         */
        void clear();
    };
}
