#include "liboom.h"

#include <stdlib.h>

int main() {
  const LiboomItem *item1 = create_liboom_item("Title1", "Key1", NULL);
  const LiboomItem *item2 = create_liboom_item("Title2", "Key2", NULL);
  const LiboomItem *item3 = create_liboom_item("Title3", "Key3", NULL);
  if (!item1 || !item2 || !item3) {
    return 1; // Memory allocation failed
  }
  LiboomItem const *const children[] = {item1, item2, NULL};
  const LiboomItem *submenu = create_liboom_item("Submenu", NULL, children);
  const LiboomItem *root_children[] = {submenu, item3, NULL};
  const LiboomItem *root = create_liboom_item("Root", NULL, root_children);
  if (!submenu || !root) {
    return 1; // Memory allocation failed
  }

  free_liboom_item(root);
  return 0;
}
