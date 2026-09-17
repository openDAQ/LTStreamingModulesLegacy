set(MODULE_NAME websocket_streaming)
set(TEST_APP test_${MODULE_NAME})

add_executable(${TEST_APP}
    streaming_test_helpers.h
    test_signal_descriptor_converter.cpp
    test_streaming.cpp
    test_websocket_client_device.cpp
    test_app.cpp
)

if (MSVC)
    target_compile_options(${TEST_APP} PRIVATE /bigobj)
endif()

target_link_libraries(${TEST_APP} PRIVATE
    ${OPENDAQ_SDK_TARGET_NAMESPACE}::${MODULE_NAME}
    ${OPENDAQ_SDK_TARGET_NAMESPACE}::opendaq
    ${OPENDAQ_SDK_TARGET_NAMESPACE}::streaming_protocol
    ${OPENDAQ_SDK_TARGET_NAMESPACE}::opendaq_test_utils
    ${OPENDAQ_SDK_TARGET_NAMESPACE}::opendaq_mocks
    gtest
)

set_target_properties(${TEST_APP} PROPERTIES DEBUG_POSTFIX _debug)
target_include_directories(${TEST_APP} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

opendaq_target_pch(${TEST_APP} <opendaq/opendaq.h> <gtest/gtest.h>)

# test_app.cpp defines main().
set_source_files_properties(test_app.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)
opendaq_target_unity_tests(${TEST_APP} BATCH_SIZE 4)

add_test(NAME ${TEST_APP}
    COMMAND $<TARGET_FILE_NAME:${TEST_APP}>
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_APP}>
)
