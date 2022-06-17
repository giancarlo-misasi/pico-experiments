#include <events/button_gesture_detector.hpp>

namespace events
{
    const int touchTimeout = 225;
    const int tapTimeout = 600;
    const int maxTouchDistanceSquared = 18.0f * 18.0f;
    const int maxTapDistanceSquared = 32.0f * 32.0f;

    ButtonGestureDetector::ButtonGestureDetector(int gestureTimeout, int pressesToDetect, GestureEvent::Type type)
        : gestureTimeout(gestureTimeout), pressesToDetect(pressesToDetect), type(type), presses(0)
    {
    }

    void ButtonGestureDetector::reset()
    {
        previous.reset();
        presses = 0;
    }

    std::optional<GestureEvent> ButtonGestureDetector::detect(const Event &ev)
    {
        if (ev.event_type() != 0) // TODO do better
        {
            reset();
            return std::nullopt;
        }

        const ButtonEvent &event = (ButtonEvent &) ev;
        switch (event.type)
        {
            case ButtonEvent::Type::BEGIN:
            {
                if (presses > 0 && !is_within_timeout(event))
                {
                    reset();
                }
                previous = event;
                break;
            }
            case ButtonEvent::Type::END:
            {
                if (is_within_timeout(event))
                {
                    presses++;
                    previous = event;

                    if (pressesToDetect == presses)
                    {
                        reset();
                        return {type};
                    }
                }
                break;
            }
        }

        return std::nullopt;
    }

    bool ButtonGestureDetector::is_within_timeout(const ButtonEvent &event)
    {
        if (!previous.has_value())
        {
            return false;
        }
        return event.time - previous.value().time < gestureTimeout;
    }
}
