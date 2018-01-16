#include "controller.h";
#include "../../nes.h";

struct AllInputs Input;

void sendReadInputSignalToControllers () {
  SET_16BIT_VALUE_TO_POINTER(APU_PAD1, 0x0100);
}

void readControllerInputs(void) {
  sendReadInputSignalToControllers();
  Input.player1.A = APU_PAD1 & 1;
  Input.player1.B = APU_PAD1 & 1;
  Input.player1.Select = APU_PAD1 & 1;
  Input.player1.Start = APU_PAD1 & 1;
  Input.player1.Up = APU_PAD1 & 1;
  Input.player1.Down = APU_PAD1 & 1;
  Input.player1.Left = APU_PAD1 & 1;
  Input.player1.Right = APU_PAD1 & 1;
}