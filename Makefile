PROJECT = Villainess
PRESET = clang20-amd64-debug
BUILD_DIR = out/build/$(PRESET)
EXE = $(firstword $(wildcard $(BUILD_DIR)/*/$(PROJECT).exe))
CONFIG ?= Debug

build:
	cmake --preset $(PRESET)
	cmake --build $(BUILD_DIR)

run: build
	"$(EXE)"

clean:
	rm -rf $(BUILD_DIR) out/install/$(PRESET)

.PHONY: setup build run clean