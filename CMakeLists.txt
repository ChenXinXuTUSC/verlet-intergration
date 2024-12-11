cmake_minimum_required(VERSION 3.20)
project(verlet-intergration)

set(OUTPUT_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX ${OUTPUT_PREFIX})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PREFIX}/lib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

include_directories(include)

find_package(
    SFML 2.6 REQUIRED
    COMPONENTS
        system window graphics network audio main
    PATHS
        SFML-2.6.2/build/install/lib/cmake/SFML
)

set(SFML_INCLUDE_DIRS SFML-2.6.2/build/install/include)
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
foreach(sfml_lib IN LISTS SFML_LIBRARIES)
    get_target_property(sfml_lib_type ${sfml_lib} TYPE)
    if(sfml_lib_type STREQUAL "SHARED_LIBRARY")
        message("${sfml_lib} is shared, will be installed to bin for runtime dependency")
        get_target_property(sfml_lib_path ${sfml_lib} LOCATION)
        install(
            FILES ${sfml_lib_path}
            DESTINATION bin/${CMAKE_BUILD_TYPE}
        )
    endif()
endforeach(sfml_lib IN LISTS SFML_LIBRARIES)



add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)
