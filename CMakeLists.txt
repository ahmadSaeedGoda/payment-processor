cmake_minimum_required(VERSION 3.22.1)

project(PaymentProcessor
    VERSION 1.0.0
    DESCRIPTION "A simplified payment processor that handles user accounts and transactions."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(${PROJECT_NAME}/include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add library for core functionality
add_library(PaymentProcessorLib ${SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp)

# Link the core library to the main executable
target_link_libraries(${PROJECT_NAME} PaymentProcessorLib pthread)

enable_testing()

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add tests subdirectory
add_subdirectory(tests)
