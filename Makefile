all: build
	@cmake --build build
	@-ctest --test-dir build --output-on-failure

build: CMakeLists.txt tests/CMakeLists.txt
	@cmake --fresh -S . -B build

.PHONY: all
