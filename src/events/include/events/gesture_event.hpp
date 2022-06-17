/**
 * @file gesture_event.hpp
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
    class GestureEvent : public Event
    {
        public:
            enum Type
            {
                Button,
                Button2
            };

        public:
            GestureEvent::Type type;

        public:
            GestureEvent(GestureEvent::Type type);
            int event_type() const;
    };
}
