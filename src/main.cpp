#include <stdint.h>

namespace PPU {

	// NES PPU registers
#define PPUCTRL   (*(volatile uint8_t*)0x2000)
#define PPUMASK   (*(volatile uint8_t*)0x2001)
#define PPUSTATUS (*(volatile uint8_t*)0x2002)
#define PPUSCROLL (*(volatile uint8_t*)0x2005)
#define PPUADDR   (*(volatile uint8_t*)0x2006)
#define PPUDATA   (*(volatile uint8_t*)0x2007)

	static const uint8_t palette[16] =
	{
		0x0F, 0x20, 0x10, 0x00, // BG palette 0
		0x0F, 0x00, 0x00, 0x00, // BG palette 1
		0x0F, 0x00, 0x00, 0x00, // BG palette 2
		0x0F, 0x00, 0x00, 0x00  // BG palette 3
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

		(void)PPUSTATUS;              // reset $2006 latch
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
		(void)PPUSTATUS; // reset latch
		PPUADDR = (uint8_t)(addr >> 8);
		PPUADDR = (uint8_t)(addr & 0xFF);
		PPUDATA = tile;
	}

	static void write(uint8_t addr_hi, uint8_t addr_lo, const uint8_t* data, uint16_t len)
	{
		(void)PPUSTATUS; // reset $2006 latch
		PPUADDR = addr_hi;
		PPUADDR = addr_lo;
		for (uint16_t i = 0; i < len; i++)
		{
			PPUDATA = data[i];
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
	PPU::print(10, 14, "HELLO JUAN");

	// Set scroll to 0,0 (important)
	(void) PPUSTATUS;
	PPUSCROLL = 0;
	PPUSCROLL = 0;

    // Enable background rendering
    PPUMASK = 0x08;

    // Main loop (NES never exits)
    while (1)
    {
        // idle forever
    }

    return 0;
}


