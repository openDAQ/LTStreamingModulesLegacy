set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
cmake_minimum_required(VERSION 3.25)

# set project variables
set(REPO_NAME LtStreamingModulesLegacy)
set(REPO_OPTION_PREFIX DAQMODULES_LT_STREAMING)

add_subdirectory(cmake)

setup_module_project(${REPO_OPTION_PREFIX} ${REPO_NAME})
setup_module_subfolders(${REPO_OPTION_PREFIX} ${REPO_NAME})
