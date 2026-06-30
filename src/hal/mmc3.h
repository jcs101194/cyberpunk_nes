#pragma once

#include <stdint.h>

#define MMC3_BANK_SELECT (*(volatile uint8_t*)0x8000)
#define MMC3_BANK_DATA   (*(volatile uint8_t*)0x8001)
#define MMC3_MIRRORING   (*(volatile uint8_t*)0xA000)
#define MMC3_PRG_RAM     (*(volatile uint8_t*)0xA001)
#define MMC3_IRQ_LATCH   (*(volatile uint8_t*)0xC000)
#define MMC3_IRQ_RELOAD  (*(volatile uint8_t*)0xC001)
#define MMC3_IRQ_DISABLE (*(volatile uint8_t*)0xE000)
#define MMC3_IRQ_ENABLE  (*(volatile uint8_t*)0xE001)

namespace MMC3
{
    void init();
    void set_chr_bank(uint8_t reg, uint8_t bank);
    void set_prg_bank(uint8_t reg, uint8_t bank);
}
