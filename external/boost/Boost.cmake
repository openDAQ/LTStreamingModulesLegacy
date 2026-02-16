include_guard(GLOBAL)

opendaq_add_required_boost_libs(
    asio
    beast
)

if (${REPO_OPTION_PREFIX}_ENABLE_CLIENT)
    opendaq_add_required_boost_libs(
        uuid
    )
endif()

if (${REPO_OPTION_PREFIX}_ENABLE_SIGGEN_INTEGRATION_TESTS)
    opendaq_add_required_boost_libs(
        program_options
    )
endif()
