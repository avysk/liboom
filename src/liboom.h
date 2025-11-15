/**
 * @file liboom.h
 * @brief Header file for Liboom library.
 */
#pragma once

typedef struct LiboomItem {
  char const *const title;
  char const *const key;
  struct LiboomItem const *const children;
} LiboomItem;

/**
 * @brief Create a LiboomItem.
 *
 * @param title The title of the item.
 * @param key The key of the item, if childern pointer is not null, this is
 *        ignored.
 * @param children The children of the item; NULL if creating a leaf.
 * @return A LiboomItem struct.
 */
const LiboomItem *create_liboom_item(char const *const title,
                                     char const *const key,
                                     LiboomItem const *const children);

void free_liboom_item(const LiboomItem *item);

int placeholder();
/*
vim: set sw=4 ts=4 sts=4 ft=c:
*/
