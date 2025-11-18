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
    ${OPENDAQ_SDK_TARGET_NAMESPACE}::test_utils
    gtest
)

set_target_properties(${TEST_APP} PROPERTIES DEBUG_POSTFIX _debug)
target_include_directories(${TEST_APP} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_test(NAME ${TEST_APP}
    COMMAND $<TARGET_FILE_NAME:${TEST_APP}>
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_APP}>
)
