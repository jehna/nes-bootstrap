#include "main.h"
#include "nes/utils.h"
#include "components/character.h"
#include "components/helloworld.h"
#include "config/palettes.h"


/**
 * This function gets called once per frame.
 * Use this file to call your "update" functions from ohter files.
 */
void update (void) {
  updateCharacter();
}

/**
 * This is run once in the startup of the game.
 * You should run "start" function from other scripts here.
 */
void start (void) {
  loadDefaultPalettes();
  startCharacter();
  startHelloWorld();
  resetScrollPosition();
};

/**
 * This gets called as many times as possible, but it can be interrupted at any
 * point by the "update" function (NES is single-threaded).
 * Do all the hard-lifting work here that should not infer with the frame rate.
 */
void mainLoop (void) {

}