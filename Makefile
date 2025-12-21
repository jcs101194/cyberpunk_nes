ROM_NAME := cyber_platform
TARGET   := nes-nrom

CXX      := mos-$(TARGET)-clang++
CXXFLAGS := -Os

all:
	mkdir -p build
	$(CXX) $(CXXFLAGS) src/main.cpp -o build/$(ROM_NAME).nes

clean:
	rm -rf build

