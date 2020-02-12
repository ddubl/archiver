# ------[CORE_DEFINITIONS]------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(
        archiver
        VERSION 0.0.1
        HOMEPAGE_URL https://github.com/danwalterlink/archiver
        LANGUAGES CXX
)
include(GNUInstallDirs)

#-------[SUBMODULES]-------------
find_package(Git QUIET)

IF(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check Submodules during build" ON)
    IF(GIT_SUBMODULE)
        message(STATUS "Checking Submodules")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT
                )
        IF(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "Git submodule --init --recursive failed with ${GIT_SUBMOD_RESULT} ")
        ENDIF()
    ENDIF()
ENDIF()

#-------ERRORCHECKING
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#-------[LIBRARIES]--------------

#-------[OpenCV]--------------
#set(OPENCV_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/lib/opencv)
#find_package(opencv REQUIRED
#        COMPONENT
#            core
#        OPTIONAL_COMPONENT
#            xphoto
#            ximgproc
#        )
#
#install(TARGETS opencv
#        LIBRARY
#            CONFIGURATIONS DEBUG
#            RUNTIME DESTINATION build/lib
#            COMPONENT core
#            INCLUDES DESTINATION /lib/opencv
#        PUBLIC_HEADER
#            COMPONENT core
#        )

# ------[MAIN_DEF]-----------
ADD_EXECUTABLE(ARCHIVER SRC/ARCHIVER.CPP)
TARGET_INCLUDE_DIRECTORIES(ARCHIVER
        PRIVATE src
    )
