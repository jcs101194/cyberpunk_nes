#include "mmc3.h"

namespace MMC3
{
    static constexpr uint8_t CHR_MODE_NORMAL = 0x00;
    static constexpr uint8_t PRG_MODE_NORMAL = 0x00;

    static constexpr uint8_t BANK_SELECT_MODE =
        CHR_MODE_NORMAL | PRG_MODE_NORMAL;

    void set_bank(uint8_t reg, uint8_t bank)
    {
        MMC3_BANK_SELECT = BANK_SELECT_MODE | (reg & 0x07);
        MMC3_BANK_DATA = bank;
    }

    void set_chr_bank(uint8_t reg, uint8_t bank)
    {
        set_bank(reg, bank);
    }

    void set_prg_bank(uint8_t reg, uint8_t bank)
    {
        set_bank(reg, bank);
    }

    void init()
    {
        MMC3_IRQ_DISABLE = 0x00;

        /*
            CHR registers:
            R0 -> 2 KB CHR bank at PPU $0000-$07FF
            R1 -> 2 KB CHR bank at PPU $0800-$0FFF
            R2 -> 1 KB CHR bank at PPU $1000-$13FF
            R3 -> 1 KB CHR bank at PPU $1400-$17FF
            R4 -> 1 KB CHR bank at PPU $1800-$1BFF
            R5 -> 1 KB CHR bank at PPU $1C00-$1FFF
        */
        set_chr_bank(0, 0);
        set_chr_bank(1, 2);
        set_chr_bank(2, 4);
        set_chr_bank(3, 5);
        set_chr_bank(4, 6);
        set_chr_bank(5, 7);

        /*
            PRG registers:
            R6 -> 8 KB PRG bank at CPU $8000-$9FFF
            R7 -> 8 KB PRG bank at CPU $A000-$BFFF

            $C000-$DFFF and $E000-$FFFF are fixed/special depending on PRG mode.
        */
        //set_prg_bank(6, 0);
        //set_prg_bank(7, 1);
    }
}
