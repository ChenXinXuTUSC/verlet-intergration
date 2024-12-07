cmake_minimum_required(VERSION 3.20)
project(verlet-intergration)

set(OUTPUT_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${OUTPUT_PREFIX})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/lib)

include_directories(include)

find_package(
    SFML 2.6
    COMPONENTS
        system window graphics network audio main
    PATHS
        SFML-2.6.2/build/Release/install/lib/cmake/SFML
)

set(SFML_INCLUDE_DIRS SFML-2.6.2/build/Release/install/include)
include_directories(${SFML_INCLUDE_DIRS})
set(
    SFML_LIBRARIES
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    sfml-main
)


add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)
