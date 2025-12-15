.PHONY: all build clean run

all: build run

build:
	cmake -S . -B build
	cmake --build build

run: build
	@mkdir -p images
	./build/raytracing

clean:
	rm -rf build
