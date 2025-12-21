#include <stdint.h>

// NES PPU registers
#define PPUCTRL   (*(volatile uint8_t*)0x2000)
#define PPUMASK   (*(volatile uint8_t*)0x2001)
#define PPUSTATUS (*(volatile uint8_t*)0x2002)
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
    while (!(PPUSTATUS & 0x80))
        ;
}

// Write a string to the nametable at a given address
static void ppu_write_string(uint16_t addr, const char* str)
{
    PPUADDR = addr >> 8;
    PPUADDR = addr & 0xFF;

    while (*str)
    {
        PPUDATA = (*str++) - 32; // ASCII → NES tile index
    }
}

static void ppu_write_tile(uint16_t addr, uint8_t tile)
{
    (void)PPUSTATUS; // reset latch
    PPUADDR = (uint8_t)(addr >> 8);
    PPUADDR = (uint8_t)(addr & 0xFF);
    PPUDATA = tile;
}

static void ppu_write(uint8_t addr_hi, uint8_t addr_lo, const uint8_t* data, uint16_t len)
{
    (void)PPUSTATUS; // reset $2006 latch
    PPUADDR = addr_hi;
    PPUADDR = addr_lo;
    for (uint16_t i = 0; i < len; i++)
    {
        PPUDATA = data[i];
    }
}

int main()
{
    // Disable rendering
    PPUMASK = 0x00;
    PPUCTRL = 0x00;

    // Wait for VBlank so PPU is ready
    wait_vblank();

	// Debugging sanity lol
	ppu_write(0x3F, 0x00, palette, 16);
	ppu_write_tile(0x2000 + 0x42, 0x21);
	ppu_write_tile(0x2000 + 0x43, 0x22);
	ppu_write_tile(0x2000 + 0x44, 0x23);

    // Write "HELLO WORLD" to nametable $2000 (top-left area)
    //ppu_write_string(0x2000 + 0x42, "HELLO WORLD");
    // Enable background rendering
    PPUMASK = 0x08; // show background

    // Main loop (NES never exits)
    while (1)
    {
        // idle forever
    }

    return 0;
}


