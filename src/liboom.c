#include "liboom.h"

#include <assert.h>
#include <stdlib.h>

const LiboomItem *create_liboom_item(char const *const, char const *const,
                                     LiboomItem const *const *);

const LiboomItem *create_liboom_leaf(char const *const title,
                                     char const *const key) {
  return create_liboom_item(title, key, NULL);
}

const LiboomItem *create_liboom_submenu(char const *const title,
                                        LiboomItem const *const *children) {
  return create_liboom_item(title, NULL, children);
}

const LiboomItem *create_liboom_item(char const *const title,
                                     char const *const key,
                                     LiboomItem const *const *children) {
  LiboomItem *item = (LiboomItem *)malloc(sizeof(LiboomItem));
  if (!item) {
    return NULL;
  }

  item->title = title;

  if (children) {
    assert(!key);
    item->key = NULL;
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
