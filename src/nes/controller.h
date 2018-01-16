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

extern struct ControllerInput player1Input;

void readControllerInputs(void);