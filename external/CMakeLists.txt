set(CMAKE_FOLDER external)
list(APPEND CMAKE_MESSAGE_CONTEXT external)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source build is not supported!")
endif()

if(NOT OPENDAQ_SDK_VERSION)
    message(FATAL_ERROR "OPENDAQ_SDK_VERSION is not set")
endif()

include(FetchContent)
find_package(openDAQ ${OPENDAQ_SDK_VERSION})

if (NOT openDAQ_FOUND)
    set(OPENDAQ_ENABLE_TESTS OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        openDAQ
        GIT_REPOSITORY https://github.com/openDAQ/openDAQ.git
        GIT_TAG v${OPENDAQ_SDK_VERSION}
        GIT_PROGRESS   ON
        SYSTEM
        FIND_PACKAGE_ARGS ${OPENDAQ_SDK_VERSION} GLOBAL
    )

    FetchContent_MakeAvailable(openDAQ)
    message(STATUS "Include opendaq_dependency macro from fetched ${FETCHCONTENT_SOURCE_DIR_OPENDAQ}/cmake/opendaq_dependency.cmake")
    include(${FETCHCONTENT_SOURCE_DIR_OPENDAQ}/cmake/opendaq_dependency.cmake)
else()
    message(STATUS "Found openDAQ in ${openDAQ_DIR}")
    message(STATUS "Include opendaq_dependency macro from found ${openDAQ_DIR}/../../../share/cmake/opendaq_dependency.cmake")
    include("${openDAQ_DIR}/../../../share/cmake/opendaq_dependency.cmake")
endif()

add_subdirectory(nlohmann_json EXCLUDE_FROM_ALL)
add_subdirectory(streaming_protocol EXCLUDE_FROM_ALL)

if (${REPO_OPTION_PREFIX}_ENABLE_TESTS)
    add_subdirectory(gtest)
endif()
