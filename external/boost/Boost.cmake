include_guard(GLOBAL)

opendaq_append_required_boost_components(
    asio
    beast
)

if (${REPO_OPTION_PREFIX}_ENABLE_SIGGEN_INTEGRATION_TESTS)
    opendaq_append_required_boost_components(
        program_options
    )
endif()

if (${REPO_OPTION_PREFIX}_ENABLE_CLIENT)
    opendaq_append_required_boost_components(
        uuid
    )
endif()
