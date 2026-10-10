include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(mytst_exec my_test.cpp)
target_link_libraries(mytst_exec PUBLIC GTest::gtest_main)
target_link_libraries(mytst_exec PUBLIC mylib)
target_include_directories(mytst_exec PUBLIC ${CMAKE_SOURCE_DIR}/my_lib)

include(GoogleTest)
gtest_discover_tests(mytst_exec)