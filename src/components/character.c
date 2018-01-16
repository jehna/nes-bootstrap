#include "character.h"
#include "../nes/sprite.h"
#include "../nes/controller.h"

unsigned int playerPosition = 0;

void updateCharacterPos (void) {
  if (player1Input.Right) {
    ++playerPosition;
  } else if (player1Input.Left) {
    --playerPosition;
  }
  SPRITES[1].xPos = SPRITES[0].xPos = playerPosition + 0x80;
}

void updateCharacter(void) {
  updateCharacterPos();
}

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

void startCharacter(void) {
  drawCharacter();
}
