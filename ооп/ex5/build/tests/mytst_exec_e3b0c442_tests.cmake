add_test([=[HypotenuseSuite.TestNormal]=]  [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests/mytst_exec]==] [==[--gtest_filter=HypotenuseSuite.TestNormal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HypotenuseSuite.TestNormal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/ksenia/Documents/GitHub/Nsu/Ð¾Ð¾Ð¿/ex5/tests/my_test.cpp:5]==]
    WORKING_DIRECTORY [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[HypotenuseSuite.TestZero]=]  [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests/mytst_exec]==] [==[--gtest_filter=HypotenuseSuite.TestZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HypotenuseSuite.TestZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/ksenia/Documents/GitHub/Nsu/Ð¾Ð¾Ð¿/ex5/tests/my_test.cpp:10]==]
    WORKING_DIRECTORY [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[HypotenuseSuite.AssertVsExpect]=]  [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests/mytst_exec]==] [==[--gtest_filter=HypotenuseSuite.AssertVsExpect]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HypotenuseSuite.AssertVsExpect]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/ksenia/Documents/GitHub/Nsu/Ð¾Ð¾Ð¿/ex5/tests/my_test.cpp:15]==]
    WORKING_DIRECTORY [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[HypotenuseRandSuite.TestRange]=]  [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests/mytst_exec]==] [==[--gtest_filter=HypotenuseRandSuite.TestRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HypotenuseRandSuite.TestRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/Users/ksenia/Documents/GitHub/Nsu/Ð¾Ð¾Ð¿/ex5/tests/my_test.cpp:25]==]
    WORKING_DIRECTORY [==[/Users/ksenia/Documents/GitHub/Nsu/ооп/ex5/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(mytst_exec_TESTS [==[HypotenuseSuite.TestNormal]==] [==[HypotenuseSuite.TestZero]==] [==[HypotenuseSuite.AssertVsExpect]==] [==[HypotenuseRandSuite.TestRange]==])
