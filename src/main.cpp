#include <stdint.h>
#include "hal/ppu.cpp"

int main()
{
    // Disable rendering
    PPUMASK = 0x00;
    PPUCTRL = 0x00;

    // Wait for VBlank so PPU is ready
	PPU::wait_vblank();
	PPU::wait_vblank();

	// Load palette
	PPU::write(0x3F, 0x00, PPU::palette, 32);
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


