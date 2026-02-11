set(CMAKE_FOLDER external)
list(APPEND CMAKE_MESSAGE_CONTEXT external)

if(NOT ${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE)
    add_subdirectory(opendaq)
endif()

opendaq_ignore_compiler_warnings()

add_subdirectory(boost)
add_subdirectory(gtest)

add_subdirectory(spdlog EXCLUDE_FROM_ALL)
add_subdirectory(nlohmann_json)
add_subdirectory(streaming_protocol)
