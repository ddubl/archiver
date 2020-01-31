# ------[GOALs]-----------------
##  building subdirs as libraries

# ------[CORE_DEFINITIONS]------
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(
    archiver
    VERSION 0.0.1
    HOMEPAGE_URL https://github.com/danwalterlink/archiver
    LANGUAGES CXX C
)
add_definitions("-std=c++2a")
#------[what is that for]------------------
include(GNUInstallDirs)

set(CMAKE_VERBOSE_MAKEFILE ON)

# -----[PKGMANAGER_CONAN_INFO]------
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
    INSTALL_DIR
        ${PROJECT_SOURCE_DIR}/DEPS
    OPTIONS
        OPENCV:CONTRIB=TRUE
    ENV
        OPENCV:-DOPENCV_EXTRA_MODULES_PATH=${OPENCVMODULES}
) #DEPS ARE AVAILABLE AS CONAN_PKG::PKGNAME

# ------[MAIN_DEF]-----------
FILE(GLOB DEF_SOURCES  "${PROJECT_SOURCE_DIR}/SRC/*.C(PP)?")
FILE(GLOB DEC_SOURCES "${PROJECT_SOURCE_DIR}/INC/*.H(PP)?")
ADD_EXECUTABLE(ARCHIVER SRC/ARCHIVER.CPP INC/IMG.H)
TARGET_SOURCES(ARCHIVER PRIVATE ${DEF_SOURCES} ${DEC_SOURCES})
TARGET_INCLUDE_DIRECTORIES(ARCHIVER
        PUBLIC
            $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/INC>
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/INC>
        PRIVATE
            ${CMAKE_SOURCE_DIR}/SRC
        )

#-------[LIBRARIES]--------------
## opencv_contrib
macro(subdirlist result curdir)
    file(glob children relative ${curdir} ${curdir}/*)
    set(dirlist /*)
    set(dirlist "")
    foreach(child ${children})
        if(is_directory ${curdir}/${child})
            list(append dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro(subdirlist)
subdirlist(cvcontrib ${cmake_current_source_dir}/lib/opencv_contrib/modules)

add_library(opencv_contrib interface)
set(libs "")
foreach(dirname in lists cvcontrib)
    file(to_cmake_path
            ${cmake_current_source_dir}/lib/opencv_contrib/modules/${dirname}
            libpath
    )

    string(regex match "(/$)?.*" libname ${dirname})
    set(main ${libpath}/include/opencv2/${libname}.hpp)

    file(glob_recurse t_head_sources "${libpath}/*.h(pp)?")
    file(glob_recurse t_lib_sources "${libpath}/*.c(pp)?")
    add_library(${libname} object ${main})
        target_sources(${libname} private ${t_libs_sources})
        target_include_directories(${libname}
                public
                    $<install_interface:${libpath}/include/opencv2>
                    $<build_interface:${libpath}/include/opencv2>
                private
                    ${libpath}/src
                    ${libpath}/include/opencv2/${libname}
                )
        set_target_properties(${libname} properties public_header ${main})
        target_link_libraries(${libname} public conan_pkg::opencv)
    list(append libs ${libname})
endforeach(dirname)

foreach(lib in lists libs)
    target_link_libraries(opencv_contrib interface $<target_objects:${lib}>)
endforeach()

install(
    targets opencv_contrib ${libs}
    library
        destination ${cmake_binary_dir}/lib
        component libraries
        namelink_component development
    public_header
        component development
)

#----------[link_main]--------------------
conan_target_link_libraries(archiver public ${conan_pkg} ${opencv_contrib})
