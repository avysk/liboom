#include "liboom.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  // Create a sample menu structure
  // Root
  // ├── Submenu 1
  // │   ├── Item 1
  // │   └── Item 2
  // ├── Sembenu 2
  // │   ├── Item 3
  // │   ├── Sumbenu 3
  // │   │   ├── Item 4
  // │   │   └── Item 5
  // │   └── Item 6
  // └── Item 7
  const LiboomItem *items[7];
  char *titles[7];
  char *keys[7];
  for (size_t i = 0; i < 7; ++i) {
    if (asprintf(&titles[i], "Item %zu", i + 1) == -1) {
      return 1;
    }
    if (asprintf(&keys[i], "Key%zu", i + 1) == -1) {
      return 1;
    }
    items[i] = create_liboom_leaf(titles[i], keys[i]);
    if (!items[i]) {
      return 1;
    }
  }
  const LiboomItem *submenus[3];
  submenus[0] = create_liboom_submenu(
      "Submenu 1", (LiboomItem const *const[]){items[0], items[1], NULL});
  if (!submenus[0]) {
    return 1;
  }
  submenus[2] = create_liboom_submenu(
      "Submenu 3", (LiboomItem const *const[]){items[3], items[4], NULL});
  if (!submenus[2]) {
    return 1;
  }
  submenus[1] = create_liboom_submenu(
      "Submenu 2",
      (LiboomItem const *const[]){items[2], submenus[2], items[5], NULL});
  if (!submenus[1]) {
    return 1;
  }
  const LiboomItem *root = create_liboom_submenu(
      "Root",
      (LiboomItem const *const[]){submenus[0], submenus[1], items[6], NULL});
  if (!root) {
    return 1;
  }

  free_liboom_item(root);

  for (size_t i = 0; i < 7; ++i) {
    free(titles[i]);
    free(keys[i]);
  }
  return 0;
}
