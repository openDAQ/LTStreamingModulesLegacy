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

#add_definitions(-DFMT_HEADER_ONLY)
#add_compile_definitions(SPDLOG_FMT_EXTERNAL=1)
find_package(Threads REQUIRED)

# options
option(${REPO_OPTION_PREFIX}_EXAMPLE_ENABLE_APP "Enable building example application" OFF)
option(${REPO_OPTION_PREFIX}_ENABLE_TESTS "Enable tests" OFF)

include(CommonUtils)
setup_repo(${REPO_OPTION_PREFIX})

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

# Set CPack variables
set(CPACK_COMPONENTS_ALL RUNTIME)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/package")

# Set the CPack generator based on the platform
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif (UNIX AND NOT APPLE)
    cmake_host_system_information(RESULT DISTRO_ID QUERY DISTRIB_ID)
    cmake_host_system_information(RESULT DISTRO_VERSION_ID QUERY DISTRIB_VERSION_ID)
    set(CPACK_SYSTEM_NAME "${DISTRO_ID}${DISTRO_VERSION_ID}")
    set(CPACK_GENERATOR "TGZ")
endif()

# Include CPack for packaging
include(CPack)
