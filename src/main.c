#include "../nes.h"
#include "main.h"

unsigned int frameCount;
unsigned int index;
const unsigned char TEXT[]={"Hello World!"};
const unsigned char PALETTE[]={
  PALETTE_COLOR_LIGHT_GRAY,
  PALETTE_COLOR_DARK_GRAY,
  PALETTE_COLOR_WHITE
};
#pragma bss-name(push, "OAM")
struct Sprite {
  unsigned char yPos;
  unsigned char spriteIndex;
  unsigned char flags;
  unsigned char xPos;
};
struct Sprite SPRITES[64];
#pragma bss-name(pop)

void vBlank () {
  SET_PPU_ADDR(PPU_ADDR_NAMETABLE_0);
  for (index = 0; index < sizeof(TEXT); ++index) {
    PPU_VRAM_IO = TEXT[index];
  }

  ++frameCount;
  updateCharacterPos();
  copyRamToPpu();

  resetScrollPosition();
  RETURN_FROM_INTERRUPT();
}

void updateCharacterPos (void) {
  SPRITES[1].xPos = SPRITES[0].xPos = frameCount + 0x80;
}

void copyRamToPpu (void) {
  PPU_SPR_ADDR = 0;
  APU_SPR_DMA = 2;
}

void main (void) {
  DISABLE_IRQ_INTERRUPT(); // We're not using IRQ interrupts for now
  DISABLE_DECIMAL_MODE(); // NES 6502 processor does not have a decimal mode

  turnOffScreen();
  loadPalette();
  resetScrollPosition();

  drawCharacter();

  turnOnScreen();

  while(1) {}
};

void drawCharacter(void) {
  SPRITES[0].xPos = 0x80;
  SPRITES[0].yPos = 0x80;
  SPRITES[0].spriteIndex = 0x01;
  SPRITES[0].flags = 0x00;

  SPRITES[1].xPos = 0x80;
  SPRITES[1].yPos = 0x88;
  SPRITES[1].spriteIndex = 0x11;
  SPRITES[1].flags = 0x00;
}

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
  SET_PPU_ADDR(PPU_ADDR_PALETTE_SPRITE_0);
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