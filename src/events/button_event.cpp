#include <events/button_event.hpp>

namespace events
{
    ButtonEvent::ButtonEvent(ButtonEvent::Type type, int time) : type(type), time(time)
    {
    }

    int ButtonEvent::event_type() const
    {
        return 0;
    }
}
