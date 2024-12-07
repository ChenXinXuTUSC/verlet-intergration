file(GLOB app_list ./*.cpp)

foreach(app ${app_list})
    get_filename_component(app_name ${app} NAME_WE)
    add_executable(${app_name} ${app})
    target_link_libraries(${app_name} src ${SFML_LIBRARIES})
endforeach(app ${app_list})
