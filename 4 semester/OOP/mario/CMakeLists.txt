cmake_minimum_required(VERSION 3.20)

project(mario)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(mario
        main.cpp
)

target_link_libraries(mario
        fltk
)