opendaq_set_cmake_folder_context(TARGET_FOLDER_NAME)

if (MSVC)
    add_compile_options(/wd4100)
endif()

if (NOT WIN32 AND ${REPO_OPTION_PREFIX}_ENABLE_SIGGEN_INTEGRATION_TESTS)
    message(STATUS "Websocket streaming signal generator tool integration test app")
    add_subdirectory(test_ws_siggen_integration)
endif()
