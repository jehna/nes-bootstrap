#include "helloworld.h"
#include "../../nes.h"

const unsigned char TEXT[]={"Hello World!"};

void drawHelloWorld (void) {
  int index = 0;
  SET_PPU_ADDR(PPU_ADDR_NAMETABLE_0);
  for (index = 0; index < sizeof(TEXT); ++index) {
    PPU_VRAM_IO = TEXT[index];
  }
}

void startHelloWorld (void) {
  drawHelloWorld();
}
