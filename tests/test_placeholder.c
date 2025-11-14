#include "liboom.h"

#include <stdio.h>

int main() {
  if (placeholder()) {
    printf("Test failed: placeholder() did not return 0\n");
    return 1;
  }
  return 0;
}
