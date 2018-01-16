#include "../../nes.h"

void resetScrollPosition(void) {
  SET_PPU_SCROLL(0, 0);
}

void turnOffScreen(void) {
  PPU_CTRL = 0;
  PPU_MASK = PPU_MASK_FLAG_SCREEN_OFF;
}

void turnOnScreen(void) {
  PPU_CTRL = PPU_CTRL_FLAG_GENERATE_NMI_AT_VBI | PPU_CTRL_FLAG_BG_TABLE_ADDRESS_1000; // screen is on, NMI on
  PPU_MASK = PPU_MASK_FLAG_SHOW_ALL;
}

void copyRamToPpu (void) {
  PPU_SPR_ADDR = 0;
  APU_SPR_DMA = 2;
}