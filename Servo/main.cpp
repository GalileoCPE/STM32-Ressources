#include "Servo.h"
#include "mbed.h"

Servo servo(D2);

int main() {
  // Active le servomoteur:
  servo.enable(90, 20000);

  // Déplace le servo de 0° à 90° en boucle:
  while (true) {
    servo.pos(0);
    wait(2);

    servo.pos(90);
    wait(2);
  }
}
