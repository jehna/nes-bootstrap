#include "../../nes.h"
#include "../main.h"
#include "controller.h"
#include "utils.h"
#include "sounds.h"


void callMainUpdateFunction () {
  update();
}

/**
 * vBlank gets called once per frame.
 */
void vBlank () {
  synchronizeMusicToFrame();
  readControllerInputs();

  callMainUpdateFunction();

  copyRamToPpu();
  RETURN_FROM_INTERRUPT();
}

/**
 * Init is the first function to be run
 */
void init () {
  DISABLE_IRQ_INTERRUPT(); // We're not using IRQ interrupts for now
  DISABLE_DECIMAL_MODE(); // NES 6502 processor does not have a decimal mode

  turnOffScreen();
  initMusic();
  initSoundEffects();
  start();
  turnOnScreen();

  while(1) {
    mainLoop();
  }
}


/**
 * This writes the NES header that's needed to launch the game in the first
 * place.
 */
#pragma rodata-name (push, "HEADER");
const unsigned char header[] = { NES_FILE_HEADER(16, 8) };
#pragma rodata-name (pop);

/**
 * Set the startup scripts:
 * Which function will be called when the:
 * - Program starts and
 * - VBLank starts (non-maskable interrupt / NMI)
 */
#pragma rodata-name (push, "VECTORS");
const void vectors = { (unsigned)vBlank, (unsigned)init };
#pragma rodata-name (pop);
