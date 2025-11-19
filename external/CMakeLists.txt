set(CMAKE_FOLDER external)
list(APPEND CMAKE_MESSAGE_CONTEXT external)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source build is not supported!")
endif()

if(NOT OPENDAQ_SDK_VERSION)
    message(FATAL_ERROR "OPENDAQ_SDK_VERSION is not set")
endif()

include(FetchContent)
find_package(openDAQ ${OPENDAQ_SDK_VERSION} GLOBAL)

if (NOT openDAQ_FOUND)
    set(OPENDAQ_ENABLE_TESTS OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        openDAQ
        GIT_REPOSITORY https://github.com/openDAQ/openDAQ.git
        GIT_TAG other/module-extract-prep
        GIT_PROGRESS   ON
        SOURCE_DIR ${FETCHCONTENT_EXTERNALS_DIR}/src/openDAQ
    )

    FetchContent_MakeAvailable(openDAQ)

    message(STATUS "openDAQ fetched source directory is detected as: ${openDAQ_SOURCE_DIR}")
    # cmake incorrectly detects openDAQ_SOURCE_DIR at repo root/core/opendaq likely caused by similar targets: openDAQ (at root) vs opendaq (at root/core/opendaq), so modify path
    include(${openDAQ_SOURCE_DIR}/../../cmake/opendaq_dependency.cmake)
else()
    message(STATUS "Found openDAQ in ${openDAQ_DIR}")
    message(STATUS "Include opendaq_dependency macro from found ${openDAQ_DIR}/../../../share/cmake/opendaq_dependency.cmake")
    include("${openDAQ_DIR}/../../../share/cmake/opendaq_dependency.cmake")
endif()

add_subdirectory(spdlog EXCLUDE_FROM_ALL)
add_subdirectory(nlohmann_json EXCLUDE_FROM_ALL)
add_subdirectory(streaming_protocol EXCLUDE_FROM_ALL)

if (${REPO_OPTION_PREFIX}_ENABLE_TESTS)
    add_subdirectory(gtest)
endif()
