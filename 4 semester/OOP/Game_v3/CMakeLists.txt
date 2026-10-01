cmake_minimum_required(VERSION 3.10)
project(Game_v3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(FLTK REQUIRED)

set(SOURCES main.cpp

        # Controller
        Controller/AbstractController.cpp
        Controller/MainMenuController.cpp
        Controller/AboutController.cpp
        Controller/GameController.cpp

        # View
        View/MainMenuView.cpp
        View/AboutView.cpp
        View/GameView.cpp

        # Model
        Model/Game.cpp
        Model/Lane.cpp
        Model/LaneRoad.cpp
        Model/Field.cpp
        Model/Coin.cpp
        Model/GameConstants.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        ${FLTK_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Controller
        ${CMAKE_SOURCE_DIR}/Model
        ${CMAKE_SOURCE_DIR}/View
        ${CMAKE_SOURCE_DIR}/Utils
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${FLTK_LIBRARIES})

# Копирование ресурсов
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources"
        COMMENT "Copying Resources..."
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} comctl32)
endif()

message(STATUS "CMake configured successfully!")