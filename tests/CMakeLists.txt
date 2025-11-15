add_executable(test_smoke test_smoke.c)
target_link_libraries(test_smoke PRIVATE Liboom::static)
add_test(NAME test_smoke COMMAND test_smoke)
