/**
 * @file event.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief TODO
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

namespace events
{
    class Event
    {
        public:
            virtual int event_type() const = 0;
    };
}
