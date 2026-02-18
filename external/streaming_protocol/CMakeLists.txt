set(STREAMING_PROTOCOL_ALWAYS_FETCH_DEPS ON CACHE BOOL "" FORCE)

if (${REPO_OPTION_PREFIX}_ENABLE_SIGGEN_INTEGRATION_TESTS)
    set(STREAMING_PROTOCOL_TOOLS ON CACHE BOOL "" FORCE)
else()
    set(STREAMING_PROTOCOL_TOOLS OFF CACHE BOOL "" FORCE)
endif()

opendaq_dependency(
    NAME                streaming_protocol
    REQUIRED_VERSION    1.2.8
    GIT_REPOSITORY      https://github.com/openDAQ/streaming-protocol-lt.git
    GIT_REF             v1.2.8-dev
    EXPECT_TARGET       daq::streaming_protocol
)
