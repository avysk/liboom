#include "liboom.h"

#include <stdlib.h>

const LiboomItem *create_liboom_item(char const *const title,
                                     char const *const key,
                                     LiboomItem const *const *children) {
  LiboomItem *item = (LiboomItem *)malloc(sizeof(LiboomItem));
  if (!item) {
    return NULL; // Memory allocation failed
  }

  item->title = title;

  if (children) {
    item->key = NULL; // Ignore key if children are provided
    item->children = children;
  } else {
    item->key = key;
    item->children = NULL;
  }
  return item;
}

void free_liboom_item(const LiboomItem *item) {
  // Start by freeing the children
  size_t i = 0;
  LiboomItem const *const *children = item->children;
  if (children) {
    while (children[i] != NULL) {
      free_liboom_item(children[i]);
      ++i;
    }
  } else {
  }
  // Finally, free the item itself
  free((void *)item);
}
