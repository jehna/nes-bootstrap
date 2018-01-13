#include "../nes.h"
#include "main.h"

unsigned int Frame_Count;
unsigned char index;
const unsigned char TEXT[]={"Hello World!"};
const unsigned char PALETTE[]={
  PALETTE_COLOR_BLACK,
  PALETTE_COLOR_DARK_GRAY,
  PALETTE_COLOR_WHITE
};

void vBlank () {
  SET_PPU_ADDR(PPU_ADDR_NAMETABLE_0);
  for (index = 0; index < sizeof(TEXT); ++index) {
    PPU_VRAM_IO = TEXT[index];
  }

  PPU_VRAM_IO = ++Frame_Count % 10 + '0';
  resetScrollPosition();
  RETURN_FROM_INTERRUPT();
}

void main (void) {
  DISABLE_IRQ_INTERRUPT(); // We're not using IRQ interrupts for now
  DISABLE_DECIMAL_MODE(); // NES 6502 processor does not have a decimal mode

  turnOffScreen();
  loadPalette();
  resetScrollPosition();
  turnOnScreen();

  while(1) {}
};

void turnOffScreen(void) {
  PPU_CTRL = 0;
  PPU_MASK = PPU_MASK_FLAG_SCREEN_OFF;
}

void resetScrollPosition(void) {
  SET_PPU_SCROLL(0, 0);
}

void turnOnScreen(void) {
  PPU_CTRL = PPU_CTRL_FLAG_GENERATE_NMI_AT_VBI | PPU_CTRL_FLAG_BG_TABLE_ADDRESS_1000; // screen is on, NMI on
  PPU_MASK = PPU_MASK_FLAG_SHOW_ALL;
}

void loadPalette(void) {
  SET_PPU_ADDR(PPU_ADDR_PALETTE_BACKGROUND_0);
  for (index = 0; index < sizeof(PALETTE); ++index) {
    PPU_VRAM_IO = PALETTE[index];
  }

  SET_PPU_ADDR_VALUE(PPU_ADDR_PALETTE_UNIVERSAL_BACKGROUND_COLOR, PALETTE_COLOR_BLACK);
}

#pragma rodata-name (push, "VECTORS");
const void vectors = { (unsigned)vBlank, (unsigned)main };
#pragma rodata-name (pop);

#pragma rodata-name (push, "HEADER");
const unsigned char header[] = { NES_FILE_HEADER(16, 8) };
#pragma rodata-name (pop);