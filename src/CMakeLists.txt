file(GLOB src_list ./*.cpp)

add_library(src SHARED ${src_list})
target_link_libraries(src PUBLIC ${SFML_LIBRARIES})
install(
    TARGETS src
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
