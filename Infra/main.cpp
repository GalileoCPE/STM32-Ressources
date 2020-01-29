#include "mbed.h"

// Elément:
#include "Infra.h"

// Pins Infrarouge:
#define pin_infra1 A1
#define pin_infra2 A2
#define pin_infra3 A3

// Infrarouge:
Infra infraFrontD(pin_infra1);
Infra infraFrontG(pin_infra2);
Infra infraBack(pin_infra3);

int main() {
  printf("STM32 Infra\r\n");

  while (1) {
    infraFrontG.mesure();
    infraFrontD.mesure();
    infraBack.mesure();
    float distanceG = infraFrontG.getDistance();
    float distanceD = infraFrontD.getDistance();
    float distanceB = infraBack.getDistance();

    printf("f_G: %f \t f_D: %f \t f_B: %f\r\n", distanceG, distanceD, distanceB);
    wait(0.1);
  }
}
