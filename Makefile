PROJECT = Villainess
TEST_PROJECT = VillainessTests
PRESET = clang20-amd64-debug
BUILD_DIR = out/build/$(PRESET)
EXE = $(firstword $(wildcard $(BUILD_DIR)/*/$(PROJECT).exe))
TEST_EXE = $(firstword $(wildcard $(BUILD_DIR)/*/$(TEST_PROJECT).exe))
CONFIG ?= Debug

build:
	cmake --preset $(PRESET)
	cmake --build $(BUILD_DIR)

run: build
	"$(EXE)"

test: build
	"$(TEST_EXE)"

clean:
	rm -rf $(BUILD_DIR) out/install/$(PRESET)

.PHONY: setup build run test clean