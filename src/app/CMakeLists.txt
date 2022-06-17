# setup the executable
project(app)
add_executable(${PROJECT_NAME} app.cpp)

# link dependencies
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_binary_info
    pico_time
    pico_multicore
    hardware_i2c
    
    devices
    bus
    events
    math
)

# create map/bin/hex file etc
pico_add_extra_outputs(${PROJECT_NAME})
