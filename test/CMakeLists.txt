include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/85087857ad10bd407cd6ed2f52f7ea9752db621f.zip
                                                   
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

enable_testing()

add_executable(
  Connect4_UnitTest
  Connect4Test.cpp
)
target_link_libraries(
  Connect4_UnitTest
  GTest::gtest_main
  libconnect4
)
target_include_directories(
    libconnect4 PUBLIC include
)

include(GoogleTest)
gtest_discover_tests(Connect4_UnitTest)
