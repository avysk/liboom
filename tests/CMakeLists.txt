add_executable(test_placeholder test_placeholder.c)
target_link_libraries(test_placeholder PRIVATE Liboom::static)
add_test(NAME test_placeholder COMMAND test_placeholder)
