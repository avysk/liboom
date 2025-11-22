#pragma once
#include "liboom.h"
void display_liboom_menu(const LiboomItem *item);
const LiboomItem *create_liboom_item(char const *const, char const *const,
                                     LiboomItem const *const *);
