#include <stdint.h>

#include "version.h"

#include "hal/ppu.h"
#include "hal/mmc3.h"

int main()
{
	MMC3::init();

    // Disable rendering
    PPU_MASK = 0x00;
    PPU_CTRL = 0x00;

    // Wait for VBlank so PPU is ready
	PPU::wait_vblank();
	PPU::wait_vblank();

	// Load palette
	PPU::write(0x3F, 0x00, PPU::palette, 32);
	// Test Draw
	PPU::write_tile(0x2026, 0x61);

	// Version Number
	PPU::print(10, 29, "Version " GAME_VERSION);

	// Set scroll to 0,0 (important)
	(void) PPU_STATUS;
	PPU_SCROLL = 0;
	PPU_SCROLL = 0;

    // Enable background rendering
    PPU_MASK = 0x1E;

	PPU::wait_vblank();

    // Main loop (NES never exits)
    while (1)
    {
        // idle forever
    }

    return 0;
}


