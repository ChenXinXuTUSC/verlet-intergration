file(GLOB src_list *.cpp)

add_library(src STATIC ${src_list})
target_link_libraries(src PRIVATE ${SFML_LIBRARIES})
install(
    TARGETS src
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
