# ------[CORE_DEFINITIONS]------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(
    archiver
    VERSION 0.0.1
    HOMEPAGE_URL https://github.com/danwalterlink/archiver
    LANGUAGES CXX
)

#-------[LIBRARIES]--------------
include(GNUInstallDirs)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
#-------[OpenCV]--------------
set(OPENCV_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/lib/opencv)

add_library(opencv)
target_include_directories(opencv /lib/opencv)
install(TARGETS opencv
        LIBRARY
            CONFIGURATIONS DEBUG
            RUNTIME DESTINATION build/lib
            COMPONENT core
            INCLUDES DESTINATION /lib/opencv
        PUBLIC_HEADER
            COMPONENT core
        )

# ------[MAIN_DEF]-----------
ADD_EXECUTABLE(ARCHIVER SRC/ARCHIVER.CPP)
TARGET_INCLUDE_DIRECTORIES(ARCHIVER
        PRIVATE src
    )
