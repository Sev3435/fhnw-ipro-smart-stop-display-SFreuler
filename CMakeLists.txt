cmake_minimum_required(VERSION 4.1)
project(fhnw_ipro_smart_stop_display_SFreuler)

set(CMAKE_CXX_STANDARD 14)

include_directories(tools)
include_directories(tools/SerialDisplay)
include_directories(tools/WifiScan)
include_directories(tools/WifiScan/WiFiScan)

add_executable(fhnw_ipro_smart_stop_display_SFreuler
        src/display.cpp
        src/WifiManager.cpp
        tools/SerialDisplay/SerialDisplay.ino
        tools/WifiScan/WiFiScan/WiFiScan.ino
        src/project.h
        src/main.cpp)
