cmake_minimum_required(VERSION 3.10.0)
project(Sky VERSION 0.1.0 LANGUAGES C CXX)

set(FLTK_DIR d:/c++/fltk/build)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mrdrnd")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mrdrnd")

find_package(FLTK REQUIRED NO_MODULE)
include_directories(${FLTK_INCLUDE_DIRS}) 
link_directories(${FLTK_LIBRARY_DIRS}) 
add_definitions(${FLTK_DEFINITIONS})

add_executable(StarSky StarSky.cpp
        Star/Star.h
        Sky/Sky.cpp
        Sky/Sky.h
        Star/Star.cpp
        View/StarSkyDrawing.cpp
        View/StarSkyDrawing.h
        Controller/SkyController.h
        Utils/RND.cpp
        Utils/RND.h
        Sky/SkySettings.h
        Sky/SkyObjectTypes.h
        Sky/SkyObject.h
        Sky/SkyObject.cpp
        View/SkyObjectDrawing.h
        View/StarDrawing.cpp
        Sky/SkyObjectTypes.cpp
        Star/MovedStar.h
        Star/MovedStar.cpp
        Sky/SkySettings.cpp
        Sky/MovedSky.cpp
        Star/SpiralStar.h
        Sky/SpiralSky.cpp
        Star/SpiralStar.cpp
        Controller/SkyController.cpp)

target_link_libraries(StarSky fltk)

include(CTest)
enable_testing()

