set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
cmake_minimum_required(VERSION 3.25)

# set project variables
set(REPO_NAME LtStreamingModulesModern)
set(REPO_OPTION_PREFIX DAQMODULES_LT_STREAMING)

add_subdirectory(cmake)
setup_repo_version("${REPO_OPTION_PREFIX}" ${REPO_NAME} "module_version")

if (NOT DEFINED ${REPO_OPTION_PREFIX}_VERSION AND DEFINED OPENDAQ_PACKAGE_VERSION)
    set(${REPO_OPTION_PREFIX}_VERSION ${OPENDAQ_PACKAGE_VERSION})
endif()

project(${REPO_NAME} VERSION ${${REPO_OPTION_PREFIX}_VERSION} LANGUAGES CXX)

setup_build_mode(${REPO_OPTION_PREFIX} ${REPO_NAME})
if (NOT ${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE)
    setup_repo(${REPO_OPTION_PREFIX})
endif()

add_subdirectory(external)

if (NOT DEFINED OPENDAQ_SDK_NAME)
    set(OPENDAQ_SDK_NAME openDAQ)
endif()

if (NOT DEFINED OPENDAQ_SDK_TARGET_NAME)
    set(OPENDAQ_SDK_TARGET_NAME opendaq)
endif()

if (NOT DEFINED OPENDAQ_SDK_TARGET_NAMESPACE)
    set(OPENDAQ_SDK_TARGET_NAMESPACE daq)
endif()

add_subdirectory(shared)
add_subdirectory(modules)

if (NOT ${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE)
    # fetch boost at latest point when list of required boost libs and headers is completed
    opendaq_setup_boost()
endif()

if (${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE AND OPENDAQ_ENABLE_TESTS OR ${REPO_OPTION_PREFIX}_ENABLE_TESTS)
#    add_subdirectory(tests)
endif()

if (${REPO_OPTION_PREFIX}_ENABLE_EXAMPLE_APP)
#    add_subdirectory(examples)
endif()

#add_subdirectory(docs)	# FIXME no docs infrastructure to be handled by cmake
