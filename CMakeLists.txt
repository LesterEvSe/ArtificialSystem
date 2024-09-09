cmake_minimum_required(VERSION 3.22)
project(ArtificialSystem)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(INCLUDE_DIRS "")
function(add_files_to_include_dirs file_list)
    foreach(file ${file_list})
        get_filename_component(file_dir ${file} DIRECTORY)
        list(APPEND INCLUDE_DIRS ${file_dir})
    endforeach()
endfunction()


file(GLOB_RECURSE PROJECT_SOURCES "Artificial/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "Artificial/*.h")

add_files_to_include_dirs(${PROJECT_HEADERS})
add_files_to_include_dirs(${PROJECT_SOURCES})


if (WIN32)
    # Find the latest Windows SDK version
    file(GLOB SDK_VERSIONS "C:/Program Files (x86)/Windows Kits/10/Include/*")
    list(SORT SDK_VERSIONS)
    list(GET SDK_VERSIONS -1 LATEST_SDK_DIR)

    # Extract version number from directory name
    string(REPLACE "C:/Program Files (x86)/Windows Kits/10/Include/" "" SDK_VERSION ${LATEST_SDK_DIR})
    set(WINDOWS_SDK_PATH "C:/Program Files (x86)/Windows Kits/10/Include/${SDK_VERSION}")

    add_files_to_include_dirs(${SDK_VERSION})
endif()

list(REMOVE_DUPLICATES INCLUDE_DIRS)
include_directories(${INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})