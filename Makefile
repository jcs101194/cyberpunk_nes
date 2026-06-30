# General
ROM_NAME := Cyber Platform
MAPPER   := nes-mmc3
CXX      := mos-$(MAPPER)-clang++

CPP_SOURCES := $(shell find . -name '*.cpp')
ASM_SOURCES := src/chr.s

# Versioning
VERSION_MAJOR := 0
VERSION_MINOR := 0
VERSION_PATCH_FILE := .version_patch
VERSION_HEADER := src/version.h

.PHONY: all version clean

all: version
	mkdir -p build
	$(CXX) -Os $(CPP_SOURCES) $(ASM_SOURCES) -o build/"$(ROM_NAME)".nes
	cp build/"$(ROM_NAME)".nes /tmp/

clean:
	rm -rf build

version:
	@if [ ! -f $(VERSION_PATCH_FILE) ]; then echo 0 > $(VERSION_PATCH_FILE); fi
	@PATCH=$$(cat $(VERSION_PATCH_FILE)); \
	NEXT=$$((PATCH + 1)); \
	echo $$NEXT > $(VERSION_PATCH_FILE); \
	echo "#pragma once" > $(VERSION_HEADER); \
	echo "" >> $(VERSION_HEADER); \
	echo "#define GAME_VERSION_MAJOR $(VERSION_MAJOR)" >> $(VERSION_HEADER); \
	echo "#define GAME_VERSION_MINOR $(VERSION_MINOR)" >> $(VERSION_HEADER); \
	echo "#define GAME_VERSION_PATCH $$NEXT" >> $(VERSION_HEADER); \
	echo "#define GAME_VERSION \"$(VERSION_MAJOR).$(VERSION_MINOR).$$NEXT\"" >> $(VERSION_HEADER); \
	echo "Building version $(VERSION_MAJOR).$(VERSION_MINOR).$$NEXT"
