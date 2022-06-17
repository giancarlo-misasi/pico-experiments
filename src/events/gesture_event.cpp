#include <events/gesture_event.hpp>

namespace events
{
    GestureEvent::GestureEvent(GestureEvent::Type type) : type(type)
    {
    }

    int GestureEvent::event_type() const
    {
        return 1;
    }
}
