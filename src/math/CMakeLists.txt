# setup the library
project(math)
add_library(${PROJECT_NAME})

# link dependencies
target_link_libraries(${PROJECT_NAME}
)

# setup headers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# setup sources
target_sources(${PROJECT_NAME}
    PRIVATE
        algorithms.cpp
)
