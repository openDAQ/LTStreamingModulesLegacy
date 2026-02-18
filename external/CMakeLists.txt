set(CMAKE_FOLDER external)
list(APPEND CMAKE_MESSAGE_CONTEXT external)

opendaq_ignore_compiler_warnings()

if (${REPO_OPTION_PREFIX}_ENABLE_TESTS AND NOT TARGET gtest)
    opendaq_module_setup_gtest("1.12.1")
endif()

# use for streaming_protocol the exact same version of spdlog as openDAQ uses
add_subdirectory(spdlog EXCLUDE_FROM_ALL)

add_subdirectory(nlohmann_json EXCLUDE_FROM_ALL)
add_subdirectory(streaming_protocol EXCLUDE_FROM_ALL)

