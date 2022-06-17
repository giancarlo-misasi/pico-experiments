/**
 * @file gesture_detector.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief TODO
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <optional>
#include "gesture_event.hpp"

namespace events
{
    class GestureDetector
    {
    public:
        virtual void reset() = 0;
        virtual std::optional<GestureEvent> detect(const Event &event) = 0;
    };
}
