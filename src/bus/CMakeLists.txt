# setup the library
project(bus)
add_library(${PROJECT_NAME})

# link dependencies
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_i2c
)

# setup headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# setup sources
target_sources(${PROJECT_NAME}
    PRIVATE
        i2c.cpp
)
