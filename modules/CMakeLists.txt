opendaq_set_cmake_folder_context(TARGET_FOLDER_NAME)

if (MSVC)
    add_compile_options(/wd4100)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

add_subdirectory(websocket_streaming_client_module)
add_subdirectory(websocket_streaming_server_module)
