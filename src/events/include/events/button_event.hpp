/**
 * @file button_event.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief TODO
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "event.hpp"

namespace events
{
    class ButtonEvent : public Event
    {
        public:
            enum Type
            {
                BEGIN,
                END
            };

        public:
            ButtonEvent::Type type;
            int time;

        public:
            ButtonEvent(ButtonEvent::Type type, int time);
            int event_type() const;
    };
}
