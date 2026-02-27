PROJECT = Villainess
TEST_PROJECT = VillainessTests
PRESET = clang20-amd64-debug
BUILD_DIR = out/build/$(PRESET)
CONFIG ?= Debug

ifeq ($(OS),Windows_NT)
EXE = $(firstword $(wildcard $(BUILD_DIR)/*/$(PROJECT).exe))
TEST_EXE = $(firstword $(wildcard $(BUILD_DIR)/*/$(TEST_PROJECT).exe))
RELEASE_NAME = $(PROJECT)_windows.exe
else
EXE = $(firstword $(wildcard $(BUILD_DIR)/$(PROJECT)))
TEST_EXE = $(firstword $(wildcard $(BUILD_DIR)/$(TEST_PROJECT)))
RELEASE_NAME = $(PROJECT)_linux
endif

RELEASE_BUILD = out/build/release

build:
	cmake --preset $(PRESET)
	cmake --build $(BUILD_DIR)

run: build
	$(EXE)

test: build
	$(TEST_EXE)

release:
	cmake -S . -B $(RELEASE_BUILD) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(RELEASE_BUILD) --config Release
	mkdir -p release
	cp $$(find $(RELEASE_BUILD) -name "$(PROJECT)*" -type f ! -name "*.ilk" ! -name "*.pdb" ! -name "*.recipe" | head -1) release/$(RELEASE_NAME)
	@echo "=== Release built: release/$(RELEASE_NAME) ==="

clean:
	rm -rf $(BUILD_DIR) $(RELEASE_BUILD) out/install/$(PRESET) release

.PHONY: build run test release clean