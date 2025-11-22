#include "setup.h"

#include "liboom.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const LiboomItem *create_test_menu(char *titles[static 7],
                                   char *keys[static 7]) {
  // Root
  // ├── Submenu 1
  // │   ├── Item 1
  // │   └── Item 2
  // ├── Submenu 2
  // │   ├── Item 3
  // │   ├── Submenu 3
  // │   │   ├── Item 4
  // │   │   └── Item 5
  // │   └── Item 6
  // └── Item 7
  const LiboomItem *items[7];
  for (size_t i = 0; i < 7; ++i) {
    items[i] = create_liboom_leaf(titles[i], keys[i]);
    if (!items[i]) {
      return NULL;
    }
  }
  const LiboomItem *submenus[3];
  submenus[0] = create_liboom_submenu(
      "Submenu 1", (LiboomItem const *const[]){items[0], items[1], NULL});
  if (!submenus[0]) {
    return NULL;
  }
  submenus[2] = create_liboom_submenu(
      "Submenu 3", (LiboomItem const *const[]){items[3], items[4], NULL});
  if (!submenus[2]) {
    return NULL;
  }
  submenus[1] = create_liboom_submenu(
      "Submenu 2",
      (LiboomItem const *const[]){items[2], submenus[2], items[5], NULL});
  if (!submenus[1]) {
    return NULL;
  }
  const LiboomItem *root = create_liboom_submenu(
      "Root",
      (LiboomItem const *const[]){submenus[0], submenus[1], items[6], NULL});
  if (!root) {
    return NULL;
  }
  return root;
}

bool to_stdin(const char *input) {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    return false;
  }

  write(pipefd[1], input, strlen(input));
  write(pipefd[1], "\n", 1);
  close(pipefd[1]);
  dup2(pipefd[0], STDIN_FILENO);
  close(pipefd[0]);

  return true;
}
