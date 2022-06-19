if(BUILD_TESTING)
    set(TEST_TARGET_NAME calendargenerator_test)
    add_executable(${TEST_TARGET_NAME} datehelper_test.cpp)

    find_package(GTest 1.11.0 REQUIRED MODULE)
    include(GoogleTest)
    gtest_add_tests(TARGET ${TEST_TARGET_NAME})

    target_link_libraries(${TEST_TARGET_NAME} PUBLIC ${TARGET_NAME} GTest::GTest)
endif()