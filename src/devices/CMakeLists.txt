# setup the library
project(devices)
add_library(${PROJECT_NAME})

# link dependencies
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_i2c
    hardware_adc
    bus
)

# setup headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# setup sources
target_sources(${PROJECT_NAME}
    PRIVATE
        led.cpp
        button.cpp
        adc.cpp
        lcd_1602.cpp
        stepper_28BYJ48.cpp
)
