#include "liboom.h"
#include "setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *titles[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  char *keys[7] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  const LiboomItem *root = NULL;
  int result = EXIT_FAILURE;

  for (size_t i = 0; i < 7; ++i) {
    if (asprintf(&(titles[i]), "Item %zu", i + 1) == -1) {
      goto cleanup;
    }
    if (asprintf(&(keys[i]), "Key %zu", i + 1) == -1) {
      goto cleanup;
    }
  }

  root = create_test_menu(titles, keys);
  if (!root) {
    goto cleanup;
  }

  to_stdin("2\n2\n0\n1");
  const char *selection = select_from_liboom_menu(root, false);

  if (strcmp(selection, "Key 3") != 0) {
    goto cleanup;
  }

  result = EXIT_SUCCESS;

cleanup:

  free_liboom_item(root);

  for (size_t i = 0; i < 7; ++i) {
    free(titles[i]);
    free(keys[i]);
  }
  return result;
}
