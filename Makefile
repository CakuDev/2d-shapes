.PHONY: build clean install start

# This Makefile is currently only compatible with Linux

build:
	@cmake -S . -B build

clean:
	@rm -rf build
	@mkdir build

compile:
	@cd build && cmake --build .

start: compile
	@cd build && ./2d-shapes