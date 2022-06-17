#include <pico/stdlib.h>
#include <pico/time.h>
#include <pico/binary_info.h>
#include <pico/multicore.h>
#include <hardware/irq.h>
#include <hardware/i2c.h>

#include <memory>

#include <bus/i2c.hpp>
#include <devices/led.hpp>
#include <devices/button.hpp>
#include <devices/adc.hpp>
#include <devices/lcd_1602.hpp>
#include <devices/stepper_28BYJ48.hpp>
#include <events/button_gesture_detector.hpp>

uint32_t get_ms_since_boot()
{
    return to_ms_since_boot(get_absolute_time());
}

void core0_main();
void core1_main();
void core1_interrupt_handler();

std::unique_ptr<devices::Adc> adc;
std::unique_ptr<devices::Lcd1602> lcd;
std::unique_ptr<devices::Stepper28BYJ48> stepper;

int main()
{
    adc = std::make_unique<devices::Adc>(devices::Adc::Input::ADC_0);
    lcd = std::make_unique<devices::Lcd1602>(std::make_unique<bus::I2c>(i2c1, 100 * 1000, 2, 3));
    
    std::array<uint, 4> stepper_pins = {4, 5, 6, 7};
    stepper = std::make_unique<devices::Stepper28BYJ48>(stepper_pins, true, 1);
    // stepper->set_pins(0b1000); // to test adc noise

    // multicore_launch_core1(core1_main);
    core0_main();
    return 0;
}

void core0_main()
{
    devices::Button button1(28);
    // events::ButtonGestureDetector detector(500, 2, events::GestureEvent::Type::Button2);

    std::vector<devices::Led> leds;
    for (int i = 8; i <= 22; ++i)
    {
        leds.push_back({i}); 
    }

    auto prev_time = get_ms_since_boot();
    while (true)
    {
        auto light = adc->read();
        // multicore_fifo_push_blocking(light);

        if (button1.is_pressed())
        {
            for (auto &led : leds) led.enable(true);
            stepper->set_angle(360);
        }

        auto curr_time = get_ms_since_boot();
        if (curr_time - prev_time > 3000)
        {
            for (auto &led : leds) led.enable(false);
            prev_time = curr_time;
        }

        if (light > 800)
        {
            stepper->set_angle(360);
        }
        else if (light < 200)
        {
            stepper->set_angle(360, false);
        }

        lcd->set_cursor(0, 0);
        lcd->clear();
        lcd->printf("Lt: %d", light);
        sleep_ms(100);

        // // Check for button events
        // auto rawEvent = button1.has_changed();
        // if (rawEvent.has_value())
        // {
        //     event_count++;

        //     events::ButtonEvent::Type type = rawEvent.value() ? events::ButtonEvent::Type::BEGIN : events::ButtonEvent::Type::END;
        //     events::ButtonEvent buttonEvent(type, get_ms_since_boot());
        //     auto gestureEvent = detector.detect(buttonEvent);
        //     if (gestureEvent.has_value())
        //     {
        //         lcd.set_cursor(1, 0);
        //         lcd.printf("Dbl: %5d", gestureEvent.value().type);
        //         sleep_ms(1000);
        //         lcd.clear();
        //     }
        // }

        // // Update tracked button state
        // button1.update();

        // // Draw some stuff to screen
        // lcd.set_cursor(0, 0);
        // lcd.printf("Welcome: %5d", x++);
        // sleep_ms(100);
    }
}

// void core1_main()
// {
//     multicore_fifo_clear_irq();
//     irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
//     irq_set_enabled(SIO_IRQ_PROC1, true);

//     while (true)
//     {
//         tight_loop_contents();
//     }
// }

// void core1_interrupt_handler()
// {
//     while (multicore_fifo_rvalid())
//     {
//         uint16_t raw = multicore_fifo_pop_blocking();
//     }

//     multicore_fifo_clear_irq();
// }
