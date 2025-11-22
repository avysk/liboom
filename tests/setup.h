#pragma once
#include "liboom.h"

const LiboomItem *create_test_menu(char *titles[static 7],
                                   char *keys[static 7]);

bool to_stdin(const char *input);
