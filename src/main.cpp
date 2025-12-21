#include <stdint.h>

// NES PPU registers
#define PPUCTRL   (*(volatile uint8_t*)0x2000)
#define PPUMASK   (*(volatile uint8_t*)0x2001)
#define PPUSTATUS (*(volatile uint8_t*)0x2002)
#define PPUADDR   (*(volatile uint8_t*)0x2006)
#define PPUDATA   (*(volatile uint8_t*)0x2007)

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

int main()
{
    // Disable rendering
    PPUMASK = 0x00;
    PPUCTRL = 0x00;

    // Wait for VBlank so PPU is ready
    wait_vblank();

    // Write "HELLO WORLD" to nametable $2000 (top-left area)
    ppu_write_string(0x2000 + 0x42, "HELLO WORLD");

    // Enable background rendering
    PPUMASK = 0x08; // show background

    // Main loop (NES never exits)
    while (1)
    {
        // idle forever
    }

    return 0;
}


