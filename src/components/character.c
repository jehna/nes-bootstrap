#include "character.h"
#include "../nes/sprite.h"
#include "../nes/controller.h"
#include "../nes/sounds.h"

unsigned int playerPosition = 0;

void updateCharacterPos (void) {
  if (Input.player1.Right) {
    ++playerPosition;
  } else if (Input.player1.Left) {
    --playerPosition;
  }

  if (Input.player1.A) {
    playSample(0);
  }
  Sprites[1].xPos = Sprites[0].xPos = playerPosition + 0x80;
}

void updateCharacter(void) {
  updateCharacterPos();
}

void drawCharacter(void) {
  Sprites[0].xPos = 0x80;
  Sprites[0].yPos = 0x80;
  Sprites[0].spriteIndex = 0x01;
  Sprites[0].flags = 0x00;

  Sprites[1].xPos = 0x80;
  Sprites[1].yPos = 0x88;
  Sprites[1].spriteIndex = 0x11;
  Sprites[1].flags = 0x00;
}

void startCharacter(void) {
  drawCharacter();
}
