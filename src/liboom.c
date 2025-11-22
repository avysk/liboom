#include "liboom.h"
#include "liboom_private.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const LiboomItem *create_liboom_leaf(char const *const title,
                                     char const *const key) {
  assert(title);
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

    size_t element_count;
    for (element_count = 0; children[element_count]; ++element_count)
      ;
    LiboomItem const **new_children;
    new_children = (LiboomItem const **)malloc((element_count + 1) *
                                               sizeof(const LiboomItem *));
    if (!new_children) {
      return NULL;
    }
    memcpy(new_children, children, element_count * sizeof(const LiboomItem *));
    new_children[element_count] = NULL;

    item->children = new_children;
  } else {
    item->key = key;
    item->children = NULL;
  }
  return item;
}

void display_liboom_menu(const LiboomItem *item) {
  assert(item);
  LiboomItem const *const *children = item->children;
  assert(children);
  printf("\n");
  if (item->title) {
    printf("=== %s ===\n", item->title);
  }
  for (size_t i = 0; children[i]; ++i) {
    printf("%2zu. %s", i + 1, children[i]->title);
    if (children[i]->children) {
      printf(" [...]");
    }
    printf("\n");
  }
}

char const *const select_from_liboom_menu(const LiboomItem *root_item,
                                          bool allow_empty_selection) {
  assert(root_item);
  assert(root_item->children);
  size_t choice;
  int res;
  size_t count;
  for (count = 1; root_item->children[count]; ++count)
    ;
  for (;;) {
    do {
      display_liboom_menu(root_item);
      if (allow_empty_selection) {
        printf("\n(Enter 0 to cancel selection or go one level up) > ");
      } else {
        printf("\n> ");
      }
      fflush(stdout);
      res = scanf("%zu", &choice);
      if (choice == 0) {
        if (allow_empty_selection) {
          return NULL;
        }
      }
      if (res == EOF) {
        clearerr(stdin);
      }
    } while (res == 0 || res == EOF || choice == 0 || choice > count);
    const LiboomItem *selected_item = root_item->children[choice - 1];
    if (selected_item->children) {
      char const *const selection =
          select_from_liboom_menu(selected_item, true);
      if (selection) {
        return selection;
      }
    } else {
      return selected_item->key;
    }
  }
}

void free_liboom_item(const LiboomItem *item) {
  LiboomItem const *const *children = item->children;
  if (children) {
    for (size_t i = 0; children[i]; ++i) {
      free_liboom_item(children[i]);
    }
    free((void *)children);
  }
  free((void *)item);
}
