#include "../nes.h"
#include "main.h"
#include <stdbool.h>

struct ControllerInput {
  bool A;
  bool B;
  bool Select;
  bool Start;
  bool Up;
  bool Down;
  bool Left;
  bool Right;
  bool test;
};

unsigned int frameCount;
unsigned int index;
struct ControllerInput player1Input;
unsigned int playerPosition = 0;
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

  readInput();

  ++frameCount;
  updateCharacterPos();
  copyRamToPpu();

  resetScrollPosition();
  RETURN_FROM_INTERRUPT();
}

void readInput(void) {
  sendReadInputSignalToControllers();
  player1Input.A = APU_PAD1 & 1;
  player1Input.B = APU_PAD1 & 1;
  player1Input.Select = APU_PAD1 & 1;
  player1Input.Start = APU_PAD1 & 1;
  player1Input.Up = APU_PAD1 & 1;
  player1Input.Down = APU_PAD1 & 1;
  player1Input.Left = APU_PAD1 & 1;
  player1Input.Right = APU_PAD1 & 1;
}

void sendReadInputSignalToControllers () {
  SET_16BIT_VALUE_TO_POINTER(APU_PAD1, 0x0100);
}

void updateCharacterPos (void) {
  if (player1Input.Right) {
    ++playerPosition;
  } else if (player1Input.Left) {
    --playerPosition;
  }
  SPRITES[1].xPos = SPRITES[0].xPos = playerPosition + 0x80;
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