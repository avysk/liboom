#include "liboom.h"

#include <stdio.h>
#include <stdlib.h>

#include "setup.h"

int main() {
  char *titles[7];
  char *keys[7];
  for (size_t i = 0; i < 7; ++i) {
    if (asprintf(&(titles[i]), "Item %zu", i + 1) == -1) {
      return 1;
    }
    if (asprintf(&(keys[i]), "Key %zu", i + 1) == -1) {
      return 1;
    }
  }

  const LiboomItem *root = create_test_menu(titles, keys);
  if (!root) {
    return 1;
  }

  to_stdin("3");
  select_from_liboom_menu(root, false);

  free_liboom_item(root);

  for (size_t i = 0; i < 7; ++i) {
    free(titles[i]);
    free(keys[i]);
  }
  return 0;
}
