enable_testing()

# Add the main test file
file(GLOB TEST_SOURCES "*.cpp")

# Create test executables and link with gtest and the core library
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE PaymentProcessorLib gtest gtest_main)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
