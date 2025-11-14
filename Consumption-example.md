# How to consume liboom in your CMake project

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyApp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- Fetch liboom ---
include(FetchContent)

FetchContent_Declare(
    liboom
    GIT_REPOSITORY gitolite:liboom.git
    GIT_TAG        main          # or v1.0.0, commit hash
    # GIT_SHALLOW    ON         # optional: shallow clone
)

FetchContent_MakeAvailable(liboom)

# --- Build app ---
add_executable(myapp src/main.c)
target_link_libraries(myapp PRIVATE Liboom::static)  # or ::shared
```
