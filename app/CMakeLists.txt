file(GLOB app_list ./*.cpp)

foreach(app ${app_list})
    get_filename_component(app_name ${app} NAME_WE)
    add_executable(${app_name} ${app})
    target_link_libraries(${app_name} ${SFML_LIBRARIES} src)
endforeach(app ${app_list})
