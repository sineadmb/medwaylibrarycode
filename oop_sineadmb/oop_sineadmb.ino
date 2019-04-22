#include "Flasher.h"

Flasher led1(13,500,500);
Flasher led2(12,10,11);

void setup() {
  
}

void loop() {
 led1.Update();
 led2.Update();
}

