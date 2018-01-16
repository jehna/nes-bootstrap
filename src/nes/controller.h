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

struct AllInputs {
  struct ControllerInput player1;
  struct ControllerInput player2;
};

extern struct AllInputs Input;

void readControllerInputs(void);