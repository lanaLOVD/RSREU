cmake_minimum_required(VERSION 3.15)
project(OOP_4413_17_Sokolova)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# FLTK

find_package(FLTK REQUIRED)

if(APPLE)
    # На macOS с Homebrew fltk-config помогает найти пути
    execute_process(
            COMMAND fltk-config --includedir
            OUTPUT_VARIABLE FLTK_INCLUDE_DIRS
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND fltk-config --prefix
            OUTPUT_VARIABLE FLTK_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(FLTK_LIB_DIR "${FLTK_PREFIX}/lib")
endif()


# Source files

set(SOURCES
        main.cpp

        controller/MenuController.cpp
        controller/GameController.cpp
        controller/AboutController.cpp

        view/MenuView.cpp
        view/GameView.cpp
        view/AboutWindow.cpp

        model/GameModel.cpp
        model/GameObject.cpp
        model/Player.cpp
        model/Enemy.cpp
        model/Coin.cpp
        model/Platform.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})


# Includes

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${FLTK_INCLUDE_DIRS}
)


# FLTK lib dir (нужно только на macOS с Homebrew)

if(APPLE AND FLTK_LIB_DIR)
    target_link_directories(${PROJECT_NAME} PRIVATE ${FLTK_LIB_DIR})
endif()


# FLTK libraries

target_link_libraries(${PROJECT_NAME} PRIVATE
        fltk
        fltk_images
)


# Threads (Linux/macOS/Windows safe)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


# Windows-specific

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 gdi32 ole32 uuid comctl32)
endif()


# macOS-specific

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            "-framework Cocoa"
    )
endif()