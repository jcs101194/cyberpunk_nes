#include "ppu.hpp"

namespace PPU {

    const uint8_t palette[32] =
    {
        0x0F, 0x30, 0x30, 0x30, // BG palette 0
        0x0F, 0x30, 0x30, 0x30, // BG palette 1
        0x0F, 0x30, 0x30, 0x30, // BG palette 2
        0x0F, 0x30, 0x30, 0x30, // BG palette 3

        // Sprite palettes: PPU $3F10-$3F1F
        0x0F, 0x30, 0x16, 0x20,
        0x0F, 0x30, 0x16, 0x20,
        0x0F, 0x30, 0x16, 0x20,
        0x0F, 0x30, 0x16, 0x20
    };

    // Simple busy-wait (NOP loop)
    void wait_vblank()
    {
        // Wait for any current vblank to end
        while (PPUSTATUS & 0x80){    }

        // Wait for next vblank to start
        while (!(PPUSTATUS & 0x80)){    }
    }

    // Write a string to the nametable at a given address
    void print(uint8_t x, uint8_t y, const char* str)
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

    void write_tile(uint16_t addr, uint8_t tile)
    {
        (void) PPUSTATUS; // reset latch
        PPUADDR = (uint8_t)(addr >> 8);
        PPUADDR = (uint8_t)(addr & 0xFF);
        PPUDATA = tile;
    }

    void write(uint8_t addr_hi, uint8_t addr_lo, const uint8_t* data, uint16_t len)
    {
        (void) PPUSTATUS; // reset $2006 latch
        PPUADDR = addr_hi;
        PPUADDR = addr_lo;
        for (uint16_t i = 0; i < len; i++)
        {
            PPUDATA = data[i];
        }
    }

    void write_sprite(uint8_t index, uint8_t y, uint8_t tile, uint8_t attr, uint8_t x)
    {
        OAMADDR = index * 4;

        OAMDATA = y;
        OAMDATA = tile;
        OAMDATA = attr;
        OAMDATA = x;
    }

    void clear_oam()
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
