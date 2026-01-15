set(CMAKE_FOLDER external)
list(APPEND CMAKE_MESSAGE_CONTEXT external)

if (NOT ${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE)
    set(OPENDAQ_REF "main")

    set(OPENDAQ_REF_FILE "${CMAKE_CURRENT_LIST_DIR}/opendaq_ref")
    if (EXISTS "${OPENDAQ_REF_FILE}")
        file(READ "${OPENDAQ_REF_FILE}" FILE_CONTENT)
        string(STRIP "${FILE_CONTENT}" FILE_CONTENT)
        if (FILE_CONTENT)
            set(OPENDAQ_REF "${FILE_CONTENT}")
        endif()
    endif()

    resolve_opendaq_dependency("${OPENDAQ_REF}")
endif()

suppress_ext_lib_warnings()
if (NOT ${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE AND ${REPO_OPTION_PREFIX}_ENABLE_TESTS)
    add_subdirectory(gtest)
endif()

add_subdirectory(boost)
add_subdirectory(spdlog EXCLUDE_FROM_ALL)
add_subdirectory(nlohmann_json)
add_subdirectory(streaming_protocol)