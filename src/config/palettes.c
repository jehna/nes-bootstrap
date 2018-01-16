#include "palettes.h"
#include "../../nes.h"

const unsigned char PALETTE[]={
  PALETTE_COLOR_LIGHT_GRAY,
  PALETTE_COLOR_DARK_GRAY,
  PALETTE_COLOR_WHITE
};

void loadDefaultPalettes (void) {
  int index;
  SET_PPU_ADDR(PPU_ADDR_PALETTE_BACKGROUND_0);
  for (index = 0; index < sizeof(PALETTE); ++index) {
    PPU_VRAM_IO = PALETTE[index];
  }
  SET_PPU_ADDR(PPU_ADDR_PALETTE_SPRITE_0);
  for (index = 0; index < sizeof(PALETTE); ++index) {
    PPU_VRAM_IO = PALETTE[index];
  }
  SET_PPU_ADDR_VALUE(PPU_ADDR_PALETTE_UNIVERSAL_BACKGROUND_COLOR, PALETTE_COLOR_BLACK);
}