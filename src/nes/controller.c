#include "controller.h";
#include "../../nes.h";

struct ControllerInput player1Input;

void sendReadInputSignalToControllers () {
  SET_16BIT_VALUE_TO_POINTER(APU_PAD1, 0x0100);
}

void readControllerInputs(void) {
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