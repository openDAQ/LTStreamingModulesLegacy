if (NOT ${REPO_OPTION_PREFIX}_BUILDING_AS_SUBMODULE)
    include(Boost.cmake)
    opendaq_complete_boost_dependency()
endif()

