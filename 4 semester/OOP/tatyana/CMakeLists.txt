cmake_minimum_required(VERSION 3.10)
project(tatyana LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# ====================== FLTK ======================
find_package(FLTK REQUIRED)

# ====================== Исходники ======================
add_executable(tatyana
        main.cpp

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
        Model/GameObject.cpp
        Model/Lane.cpp
        Model/LaneRoad.cpp
        Model/Field.cpp
        Model/Player.cpp
        Model/Vehicle.cpp
        Model/Coin.cpp
        Model/Road.cpp

        # Utils
        Utils/RND.cpp
)

target_include_directories(tatyana PRIVATE
        ${FLTK_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Controller
        ${CMAKE_SOURCE_DIR}/Model
        ${CMAKE_SOURCE_DIR}/View
        ${CMAKE_SOURCE_DIR}/Utils
)

target_link_libraries(tatyana PRIVATE ${FLTK_LIBRARIES})

# Копирование ресурсов
add_custom_command(TARGET tatyana POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:tatyana>/Resources"
        COMMENT "Copying Resources..."
)

message(STATUS "CMake configured successfully!")