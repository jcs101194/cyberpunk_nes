// ppu.hpp
#ifndef PPU_HPP
#define PPU_HPP

#include <stdint.h>

namespace PPU
{
	// NES PPU registers
    #define PPUCTRL    (*(volatile uint8_t*)0x2000) // PPU control register: selects nametable, pattern tables, sprite size, NMI-on-vblank
    #define PPUMASK    (*(volatile uint8_t*)0x2001) // PPU mask register: enables/disables background, sprites, left-edge rendering, color effects
    #define PPUSTATUS  (*(volatile uint8_t*)0x2002) // PPU status register: read this to check vblank; reading also resets the PPUADDR/PPUSCROLL write latch
    #define OAMADDR    (*(volatile uint8_t*)0x2003) // OAM address register: selects which byte of sprite memory/OAM you are about to read or write
    #define OAMDATA    (*(volatile uint8_t*)0x2004) // OAM data register: reads/writes sprite/OAM data at OAMADDR, then auto-increments OAMADDR
    #define PPUSCROLL  (*(volatile uint8_t*)0x2005) // PPU scroll register: write twice, first X scroll then Y scroll
    #define PPUADDR    (*(volatile uint8_t*)0x2006) // PPU VRAM address register: write twice, first high byte then low byte of the PPU address
    #define PPUDATA    (*(volatile uint8_t*)0x2007) // PPU VRAM data register: reads/writes data at PPUADDR, then auto-increments PPUADDR

    void wait_vblank();
    void write(uint8_t high, uint8_t low, const uint8_t* data, uint16_t len);
    void print(uint8_t x, uint8_t y, const char* text);
}

#endif
