ROM_NAME := Cyber Platform
TARGET   := nes-nrom

CXX      := mos-$(TARGET)-clang++
CXXFLAGS := -Os

all:
	mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp src/chr.s -o build/"$(ROM_NAME)".nes
	cp build/"$(ROM_NAME)".nes /tmp/

clean:
	rm -rf build

