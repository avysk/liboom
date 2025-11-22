all: build
	@cmake --build build

build: CMakeLists.txt tests/CMakeLists.txt
	@cmake --fresh -S . -B build -DCMAKE_BUILD_TYPE=Debug

install: all
	@cmake --install build

test: all
	@ctest --test-dir build --output-on-failure -T memcheck

.PHONY: all install test
