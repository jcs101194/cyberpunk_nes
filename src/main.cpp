#include <stdint.h>

namespace PPU {

	// NES PPU registers
	#define PPUCTRL    (*(volatile uint8_t*)0x2000) // PPU control register: selects nametable, pattern tables, sprite size, NMI-on-vblank
	#define PPUMASK    (*(volatile uint8_t*)0x2001) // PPU mask register: enables/disables background, sprites, left-edge rendering, color effects
	#define PPUSTATUS  (*(volatile uint8_t*)0x2002) // PPU status register: read this to check vblank; reading also resets the PPUADDR/PPUSCROLL write latch
	#define OAMADDR    (*(volatile uint8_t*)0x2003) // OAM address register: selects which byte of sprite memory/OAM you are about to read or write
	#define OAMDATA    (*(volatile uint8_t*)0x2004) // OAM data register: reads/writes sprite/OAM data at OAMADDR, then auto-increments OAMADDR
	#define PPUSCROLL  (*(volatile uint8_t*)0x2005) // PPU scroll register: write twice, first X scroll then Y scroll
	#define PPUADDR    (*(volatile uint8_t*)0x2006) // PPU VRAM address register: write twice, first high byte then low byte of the PPU address
	#define PPUDATA    (*(volatile uint8_t*)0x2007) // PPU VRAM data register: reads/writes data at PPUADDR, then auto-increments PPUADDR


	static const uint8_t palette[16] =
	{
		0x0F, 0x30, 0x30, 0x30, // BG palette 0
		0x0F, 0x30, 0x30, 0x30, // BG palette 1
		0x0F, 0x30, 0x30, 0x30, // BG palette 2
		0x0F, 0x30, 0x30, 0x30  // BG palette 3
	};

	// Simple busy-wait (NOP loop)
	static void wait_vblank()
	{
		// Wait for any current vblank to end
		while (PPUSTATUS & 0x80){    }

		// Wait for next vblank to start
		while (!(PPUSTATUS & 0x80)){    }
	}

	// Write a string to the nametable at a given address
	static void print(uint8_t x, uint8_t y, const char* str)
	{
		uint16_t addr = 0x2000 + (y * 32) + x;

		(void) PPUSTATUS;              // reset $2006 latch
		PPUADDR = addr >> 8;
		PPUADDR = addr & 0xFF;

		while (*str)
		{
			PPUDATA = (uint8_t)(*str - 32);
			str++;
		}
	}

	static void write_tile(uint16_t addr, uint8_t tile)
	{
		(void) PPUSTATUS; // reset latch
		PPUADDR = (uint8_t)(addr >> 8);
		PPUADDR = (uint8_t)(addr & 0xFF);
		PPUDATA = tile;
	}

	static void write(uint8_t addr_hi, uint8_t addr_lo, const uint8_t* data, uint16_t len)
	{
		(void) PPUSTATUS; // reset $2006 latch
		PPUADDR = addr_hi;
		PPUADDR = addr_lo;
		for (uint16_t i = 0; i < len; i++)
		{
			PPUDATA = data[i];
		}
	}

	static void write_sprite(uint8_t index, uint8_t y, uint8_t tile, uint8_t attr, uint8_t x)
	{
		OAMADDR = index * 4;

		OAMDATA = y;
		OAMDATA = tile;
		OAMDATA = attr;
		OAMDATA = x;
	}

	static void clear_oam()
	{
		OAMADDR = 0x00;

		for (uint16_t i = 0; i < 64; i++)
		{
			OAMDATA = 0xFF; // Y offscreen
			OAMDATA = 0x00; // tile
			OAMDATA = 0x00; // attributes
			OAMDATA = 0x00; // X
		}
	}

}

int main()
{
    // Disable rendering
    PPUMASK = 0x00;
    PPUCTRL = 0x00;

    // Wait for VBlank so PPU is ready
	PPU::wait_vblank();
	PPU::wait_vblank();

	// Load palette
	PPU::write(0x3F, 0x00, PPU::palette, 16);
	PPU::print(10, 1, "HELLO JUAN");

	// Set scroll to 0,0 (important)
	(void) PPUSTATUS;
	PPUSCROLL = 0;
	PPUSCROLL = 0;

    // Enable background rendering
    //PPUMASK = 0x08;
    PPUMASK = 0x1E;

	PPU::wait_vblank();

    // Main loop (NES never exits)
    while (1)
    {
        // idle forever
    }

    return 0;
}


