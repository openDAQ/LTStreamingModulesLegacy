set(CMAKE_FOLDER external)
list(APPEND CMAKE_MESSAGE_CONTEXT external)

setup_module_default_dependencies(${REPO_OPTION_PREFIX})

add_subdirectory(spdlog EXCLUDE_FROM_ALL)
add_subdirectory(nlohmann_json)
add_subdirectory(streaming_protocol)
