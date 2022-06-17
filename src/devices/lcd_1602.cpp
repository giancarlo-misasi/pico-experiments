#include <devices/lcd_1602.hpp>
#include <string>
#include <cstdarg>
#include <hardware/i2c.h>

#define LCD_CHARACTER 1
#define LCD_COMMAND 0
#define LCD_MAX_LINES 2
#define LCD_MAX_CHARS 16
#define LCD_DELAY_US 600

namespace devices
{
    const int LCD_CLEARDISPLAY = 0x01;
    const int LCD_RETURNHOME = 0x02;
    const int LCD_ENTRYMODESET = 0x04;
    const int LCD_DISPLAYCONTROL = 0x08;
    const int LCD_CURSORSHIFT = 0x10;
    const int LCD_FUNCTIONSET = 0x20;
    const int LCD_SETCGRAMADDR = 0x40;
    const int LCD_SETDDRAMADDR = 0x80;
    const int LCD_ENTRYSHIFTINCREMENT = 0x01;
    const int LCD_ENTRYLEFT = 0x02;
    const int LCD_BLINKON = 0x01;
    const int LCD_CURSORON = 0x02;
    const int LCD_DISPLAYON = 0x04;
    const int LCD_MOVERIGHT = 0x04;
    const int LCD_DISPLAYMOVE = 0x08;
    const int LCD_5x10DOTS = 0x04;
    const int LCD_2LINE = 0x08;
    const int LCD_8BITMODE = 0x10;
    const int LCD_BACKLIGHT = 0x08;
    const int LCD_ENABLE_BIT = 0x04;

    // By default these LCD display drivers are on bus address 0x27
    static int addr = 0x27; // TODO

    inline void i2c_write_byte_blocking(i2c_inst_t *i2c, uint8_t val)
    {
        i2c_write_blocking(i2c, addr, &val, 1, false);
    }

    void lcd_toggle_enable(i2c_inst_t *i2c, uint8_t val)
    {
        // Toggle enable pin on LCD display
        // We cannot do this too quickly or things don't work
        sleep_us(LCD_DELAY_US);
        i2c_write_byte_blocking(i2c, val | LCD_ENABLE_BIT);
        sleep_us(LCD_DELAY_US);
        i2c_write_byte_blocking(i2c, val & ~LCD_ENABLE_BIT);
        sleep_us(LCD_DELAY_US);
    }

    void lcd_send_byte(i2c_inst_t *i2c, uint8_t val, int mode)
    {
        uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
        uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

        i2c_write_byte_blocking(i2c, high);
        lcd_toggle_enable(i2c, high);
        i2c_write_byte_blocking(i2c, low);
        lcd_toggle_enable(i2c, low);
    }

    inline void lcd_clear(i2c_inst_t *i2c)
    {
        lcd_send_byte(i2c, LCD_CLEARDISPLAY, LCD_COMMAND);
    }

    inline void lcd_set_cursor(i2c_inst_t *i2c, int line, int position)
    {
        lcd_send_byte(i2c, line == 0 ? 0x80 + position : 0xC0 + position, LCD_COMMAND);
    }

    inline void lcd_write_char(i2c_inst_t *i2c, char val)
    {
        lcd_send_byte(i2c, val, LCD_CHARACTER);
    }

    void lcd_write_string(i2c_inst_t *i2c, const char *s)
    {
        while (*s)
        {
            lcd_write_char(i2c, *s++);
        }
    }

    void lcd_init(i2c_inst_t *i2c)
    {
        lcd_send_byte(i2c, 0x03, LCD_COMMAND);
        lcd_send_byte(i2c, 0x03, LCD_COMMAND);
        lcd_send_byte(i2c, 0x03, LCD_COMMAND);
        lcd_send_byte(i2c, 0x02, LCD_COMMAND);

        lcd_send_byte(i2c, LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
        lcd_send_byte(i2c, LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
        lcd_send_byte(i2c, LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
        lcd_clear(i2c);
    }

    Lcd1602::Lcd1602(std::unique_ptr<bus::I2c> _i2c) : i2c{std::move(_i2c)}
    {
        lcd_init(i2c->get_instance());
    }

    void Lcd1602::set_cursor(int line, int position)
    {
        lcd_set_cursor(i2c->get_instance(), line, position);
    }

    void Lcd1602::printf(const char *format, ...)
    {
        char message[16];

        va_list args;
        va_start(args, format);
        vsnprintf(message, 16, format, args);
        va_end(args);

        lcd_write_string(i2c->get_instance(), message);
    }

    void Lcd1602::clear()
    {
        lcd_clear(i2c->get_instance());
    }
}
