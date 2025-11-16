# Liboom

## Introduction

Liboom is a lightweight C library designed to facilitate using text
menus in terminal applications. It provides a simple API to create and manage
menus and handle user input.

Unlike more complex menu libraries, Liboom *does not require switching terminal
to a raw mode* and operates in the standard terminal mode (think `printf` and
`scanf`).

Liboom should work on any POSIX-compliant system with a C compiler, supporting
C11 standard. I develop it on FreeBSD.

## Installation and usage

There are two ways to use Liboom in your project: with our without CMake.

### Using CMake

If your project uses CMake, you don not need to install Liboom system-wide. Instead,
add the following lines to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
    liboom
    GIT_REPOSITORY https://github.com/avysk/liboom.git
    GIT_TAG        <tag you want to use>
)

FetchContent_MakeAvailable(liboom)

target_link_libraries(<your app> PRIVATE Liboom::static)
```

### Not using CMake

In this case you need to build and install Liboom system-wide. I suggest you to
link your application with Liboom's shared library.

Build and installation steps for Liboom are described below. When it is
installed, you can link your application with `-loom` flag.

### Usage in your code

Start by including the Liboom header:

```c
#include <liboom/liboom.h>
```

Then create leaf menu items using `liboom_create_leaf()` function:

```c
LiboomItem *item = create_liboom_leaf("Item title", "item key");
```

Here "item key" is a string that will be returned when the user selects this
item.

Then create submenus, supplying to them a NULL-terminated array of pointers to
`LiboomItem` objects (which can be leaf items or other submenus):

```c
LiboomItem *item1, *item2;
// create leaf items for item1 and item2
LiboomItem const *const submenu_items[] = { item1, item2, NULL };
LiboomItem *submenu = create_liboom_submenu("Submenu title", submenu_items);
```

Notice that:

- A submenu will use exactly the passed items, so do not free them.
- When you will finally free the root menu with `loom_free_item()`, all its
  subitems will be freed too recursively.

After you created the root menu, you can ask Liboom to ask the user for
selection:

```c
char const*const selected_key = select_from_liboom_menu(root_menu);
```

You will get back the "item key" of the selected leaf item.

When you are done, free the root menu:

```c
free_liboom_item(root_menu);
```

As said before, all subitems will be freed too (recursively, i.e children,
children of children, etc.). Notice that items' titles and keys are not freed,
as they are supposed to be string literals or managed by the user. Similarly,
that if some of them are variables, do not let them run out of scope while you
are still using the menu.

## Building and installing Liboom

To build and install Liboom system-wide, follow these steps:

Requirements: CMake, ninja build system (see below for alternative), C11-capable
C compiler.

1. Clone the repository.
2. Run `make`.
3. Run `make install` as root.

### Alternative build without ninja

In this case you will need `make`.

1. Clone the repository.
2. Run `cmake -B build -G "Unix Makefiles"`.
3. `cd build`.
4. Run `make`.
5. Run `make install` as root.

### Documentation

If you have `doxygen` installed, the documentation will be generated during the
build process in the `docs/html` folder.

### Testing

The tests are built during the build process. To run them, after building, run
`make test` (valgrind is required). The tests will be run under valgrind.
