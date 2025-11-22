add_executable(test_smoke test_smoke.c setup.c)
target_link_libraries(test_smoke PRIVATE Liboom::static)
add_test(NAME test_smoke COMMAND test_smoke)

add_executable(test_basic_selection test_basic_selection.c setup.c)
target_link_libraries(test_basic_selection PRIVATE Liboom::static)
add_test(NAME test_basic_selection COMMAND test_basic_selection)

add_executable(test_select_submenu test_select_submenu.c setup.c)
target_link_libraries(test_select_submenu PRIVATE Liboom::static)
add_test(NAME test_select_submenu COMMAND test_select_submenu)

add_executable(test_select_submenu2 test_select_submenu2.c setup.c)
target_link_libraries(test_select_submenu2 PRIVATE Liboom::static)
add_test(NAME test_select_submenu2 COMMAND test_select_submenu2)

add_executable(test_select_back test_select_back.c setup.c)
target_link_libraries(test_select_back PRIVATE Liboom::static)
add_test(NAME test_select_back COMMAND test_select_back)

add_executable(test_select_back2 test_select_back2.c setup.c)
target_link_libraries(test_select_back2 PRIVATE Liboom::static)
add_test(NAME test_select_back2 COMMAND test_select_back2)

add_executable(test_select_back3 test_select_back3.c setup.c)
target_link_libraries(test_select_back3 PRIVATE Liboom::static)
add_test(NAME test_select_back3 COMMAND test_select_back3)

add_executable(test_select_back4 test_select_back4.c setup.c)
target_link_libraries(test_select_back4 PRIVATE Liboom::static)
add_test(NAME test_select_back4 COMMAND test_select_back4)
