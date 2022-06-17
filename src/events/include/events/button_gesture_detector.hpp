/**
 * @file button_gesture_detector.hpp
 * @author Giancarlo Misasi (grmisasi@uwaterloo.ca)
 * @brief public:
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "button_event.hpp"
#include "gesture_detector.hpp"

namespace events
{
    class ButtonGestureDetector : public GestureDetector
    {
        int gestureTimeout;
        int pressesToDetect;
        GestureEvent::Type type;
        std::optional<ButtonEvent> previous;
        int presses;

    public:
        ButtonGestureDetector(int gestureTimeout, int pressesToDetect, GestureEvent::Type type);
        virtual void reset();
        virtual std::optional<GestureEvent> detect(const Event &event);

    private:
        bool is_within_timeout(const ButtonEvent &event);
    };
}
