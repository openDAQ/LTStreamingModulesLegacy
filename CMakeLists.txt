set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set project variables
set(REPO_NAME lt_streaming_modules)
set(REPO_OPTION_PREFIX LT_STREAMING_MODULES)

file(READ "repo_version" repo_version)
string(STRIP ${repo_version} repo_version)
string(REGEX REPLACE "^([0-9]+\\.[0-9]+\\.[0-9]+).*" "\\1" repo_version_major_minor_patch "${repo_version}")
set(REPO_VERSION "${repo_version_major_minor_patch}")

project(${REPO_NAME}
    LANGUAGES CXX
    VERSION ${REPO_VERSION}
)

# set SDK variables
set(OPENDAQ_SDK_NAME openDAQ)
set(OPENDAQ_SDK_TARGET_NAME opendaq)
set(OPENDAQ_SDK_TARGET_NAMESPACE daq)

file(READ "opendaq_version" sdk_version)
string(STRIP ${sdk_version} sdk_version)
string(REGEX REPLACE "^([0-9]+\\.[0-9]+\\.[0-9]+).*" "\\1" sdk_version_major_minor_patch "${sdk_version}")
set(OPENDAQ_SDK_VERSION "${sdk_version_major_minor_patch}")

list(APPEND CMAKE_MESSAGE_CONTEXT ${REPO_NAME})
set(CMAKE_MESSAGE_CONTEXT_SHOW ON CACHE BOOL "Show CMake message context")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

get_filename_component(ROOT_DIR ${CMAKE_SOURCE_DIR} REALPATH)
set(FETCHCONTENT_EXTERNALS_DIR ${ROOT_DIR}/build/__external CACHE PATH "FetchContent folder prefix")

add_definitions(-DFMT_HEADER_ONLY)

# options
option(${REPO_OPTION_PREFIX}_EXAMPLE_ENABLE_APP "Enable building example application" OFF)
option(${REPO_OPTION_PREFIX}_ENABLE_TESTS "Enable tests" OFF)

include(CommonUtils)
setup_repo(${REPO_OPTION_PREFIX})

if (${REPO_OPTION_PREFIX}_ENABLE_TESTS)
    message(STATUS "Unit tests are ENABLED")
    enable_testing()
endif()

add_subdirectory(external)
add_subdirectory(shared)
add_subdirectory(modules)
if (${REPO_OPTION_PREFIX}_ENABLE_TESTS)
#    add_subdirectory(tests)
endif()
if (${REPO_OPTION_PREFIX}_EXAMPLE_ENABLE_APP)
#    add_subdirectory(examples)
endif()
#add_subdirectory(docs)		# FIXME no docs infrastructure to be handled by cmake 
