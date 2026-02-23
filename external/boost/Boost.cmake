include_guard(GLOBAL)

opendaq_append_required_boost_components(
    asio
    beast
)

if (DAQMODULES_LT_STREAMING_ENABLE_SIGGEN_INTEGRATION_TESTS)
    opendaq_append_required_boost_components(
        program_options
    )
endif()

if (DAQMODULES_LT_STREAMING_ENABLE_CLIENT)
    opendaq_append_required_boost_components(
        uuid
    )
endif()
