file(GLOB test_list ./*.cpp)

foreach(test ${test_list})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    target_link_libraries(${test_name} src ${SFML_LIBRARIES})
endforeach(test ${test_list})
