# ------[CORE_DEFINITIONS]------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(
    archiver
    VERSION 0.0.1
    HOMEPAGE_URL https://github.com/danwalterlink/archiver
    LANGUAGES CXX C
)
add_definitions("-std=c++2a")
include(GNUInstallDirs)

set(CMAKE_VERBOSE_MAKEFILE ON)

# -----[PKGMANAGER_CONAN_INFO]hhhkkjkjkjjjar------
IF(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake")
ENDIF()

IF(NOT EXISTS ${CMAKE_BINARY_DIR}/lib)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib/headers)
ENDIF()

include(${CMAKE_BINARY_DIR}/conan.cmake)
set(opencvModules "${CMAKE_SOURCE_DIR}/lib/opencv_contrib/modules")
## CONAN_SETUP
# libs & pkgs -> conanfile.txt
conan_cmake_run(
    CONANFILE conanfile.txt
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
#    INSTALL_DIR
#        ${PROJECT_SOURCE_DIR}/deps
#    OPTIONS
#        opencv:contrib=True
#    ENV
#        opencv:-DOPENCV_EXTRA_MODULES_PATH=${opencvModules}
) #deps are available as CONAN_PKG::pkgname


# ------[MAIN_DEF]-----------
file(GLOB def_SOURCES  "${PROJECT_SOURCE_DIR}/src/*.c(pp)?")
file(GLOB dec_SOURCES "${PROJECT_SOURCE_DIR}/inc/*.h(pp)?")
add_executable(archiver src/Archiver.cpp inc/img.h)
target_sources(archiver PRIVATE ${def_SOURCES} ${dec_SOURCES})
target_include_directories(archiver
        PUBLIC
            $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/inc>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/inc>
        PRIVATE
            ${CMAKE_SOURCE_DIR}/src
        )

#-------[LIBRARIES]--------------
## OPENCV_CONTRIB
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist /*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO(SUBDIRLIST)
SUBDIRLIST(CVCONTRIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_contrib/modules)

add_library(OPENCV_CONTRIB INTERFACE)
set(libs "")
FOREACH(DIRNAME IN LISTS CVCONTRIB)
    file(TO_CMAKE_PATH
            ${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_contrib/modules/${DIRNAME}
            LIBPATH
    )

    string(REGEX MATCH "(/$)?.*" libName ${DIRNAME})
    set(MAIN ${LIBPATH}/include/opencv2/${libName}.hpp)

    file(GLOB_RECURSE t_HEAD_SOURCES "${LIBPATH}/*.h(pp)?")
    file(GLOB_RECURSE t_LIB_SOURCES "${LIBPATH}/*.c(pp)?")
    add_library(${libName} OBJECT ${MAIN})
        target_sources(${libName} PRIVATE ${t_LIBS_SOURCES})
        target_include_directories(${libName}
                PUBLIC
                    $<INSTALL_INTERFACE:${LIBPATH}/include/opencv2>
                    $<BUILD_INTERFACE:${LIBPATH}/include/opencv2>
                PRIVATE
                    ${LIBPATH}/src
                    ${LIBPATH}/include/opencv2/${libName}
                )
        set_target_properties(${libName} PROPERTIES PUBLIC_HEADER ${MAIN})
        target_link_libraries(${libName} PUBLIC CONAN_PKG::opencv)
    list(APPEND libs ${libName})
ENDFOREACH(DIRNAME)

FOREACH(lib IN LISTS libs)
    target_link_libraries(OPENCV_CONTRIB INTERFACE $<TARGET_OBJECTS:${lib}>)
ENDFOREACH()

INSTALL(
    TARGETS OPENCV_CONTRIB ${libs}
    LIBRARY
        DESTINATION ${CMAKE_BINARY_DIR}/lib
        COMPONENT Libraries
        NAMELINK_COMPONENT Development
    PUBLIC_HEADER
        COMPONENT Development
)

#----------[LINK_MAIN]--------------------
conan_target_link_libraries(archiver PUBLIC ${CONAN_PKG} ${OPENCV_CONTRIB})
