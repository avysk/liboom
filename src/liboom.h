/**
 * @file liboom.h
 * @brief Header file for Liboom library.
 */
#pragma once

typedef struct LiboomItem {
  char const *title;
  char const *key;
  const struct LiboomItem *const *children;
} LiboomItem;

/**
 * @brief Create a LiboomItem which is a menu leaf (no children).
 *
 * @param title The title of the item.
 * @param key The key of the item.
 * @retval NULL on memory allocation failure.
 * @retval non-NULL pointer to the created LiboomItem on success.
 *
 * @note The created LiboomItem must be freed using free_liboom_item() called on
 *       a root item; all its children will be freed recursively.
 *
 * @see free_liboom_item()
 *
 * @since 1.0.0
 */
const LiboomItem *create_liboom_leaf(char const *const title,
                                     char const *const key);

/**
 * @brief Create a LiboomItem which is a submenu (has children).
 *
 * @param title The title of the item.
 * @param children A NULL-terminated array of pointers to LiboomItem objects
 *        representing the children of this submenu. The children can be both
 *        leaves and submenus.
 * @retval NULL on memory allocation failure.
 * @retval non-NULL pointer to the created LiboomItem on success.
 *
 * @note The created LiboomItem must be freed using free_liboom_item() called on
 *       a root item; all its children will be freed recursively.
 *
 * @see free_liboom_item()
 *
 * @since 1.0.0
 */
const LiboomItem *create_liboom_submenu(char const *const title,
                                        LiboomItem const *const *children);

/**
 * @brief Free a LiboomItem and all its children recursively.
 *
 * @param item The pointer to the LiboomItem to free.
 *
 * @note This function should be called only on root item created. This function
 *        does not free titles or keys passed to create_liboom_item() priorly.
 *
 * @see create_liboom_item()
 *
 * @since 1.0.0
 */
void free_liboom_item(const LiboomItem *item);

/*
vim: set sw=4 ts=4 sts=4 ft=c:
*/
