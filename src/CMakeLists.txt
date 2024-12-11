file(GLOB src_list *.cpp)

add_library(src SHARED ${src_list})
target_link_libraries(src PRIVATE ${SFML_LIBRARIES})
install(
    TARGETS src
    LIBRARY DESTINATION bin/${CMAKE_BUILD_TYPE}
    ARCHIVE DESTINATION lib/${CMAKE_BUILD_TYPE}
)
