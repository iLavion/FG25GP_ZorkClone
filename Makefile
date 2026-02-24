PROJECT = FG25GP_ZorkClone
PRESET = clang20-amd64-debug
BUILD_DIR = out/build/$(PRESET)
EXE = $(firstword $(wildcard $(BUILD_DIR)/*/$(PROJECT).exe))
CONFIG ?= Debug

setup:
	@command -v cmake >/dev/null 2>&1 || { echo "CMake not found!"; exit 1; }
	@command -v clang++ >/dev/null 2>&1 || { echo "Clang++ not found!"; exit 1; }
	@command -v ninja >/dev/null 2>&1 || { echo "Ninja not found!"; exit 1; }
	@echo "All prerequisites OK."

build:
	cmake --preset $(PRESET)
	cmake --build $(BUILD_DIR)

run: build
	"$(EXE)"

clean:
	rm -rf $(BUILD_DIR) out/install/$(PRESET)

.PHONY: setup build run clean