#include "mbed.h"

// Elément:
#include "Moteur.h"

// Pins des moteurs:
#define pins_moteurG_enA_in1_in2 D7, D14, D15
#define pins_moteurD_enB_in1_in2 D8, D11, D12

// Moteurs:
Moteur moteurG(pins_moteurG_enA_in1_in2);
Moteur moteurD(pins_moteurD_enB_in1_in2);

int main() {
  printf("STM32 Moteur\r\n");

  while (true) {
    printf("Marche avant...\r\n");
    moteurG.turn(0.1f);
    moteurD.turn(0.1f);
    wait(4);

    moteurG.stop();
    moteurD.stop();
    printf("Stop\r\n");
    wait(2);

    printf("Marche arriere...\r\n");
    moteurG.turn(-0.1f);
    moteurD.turn(-0.1f);
    wait(4);

    moteurG.stop();
    moteurD.stop();
    printf("Stop\r\n");
    wait(2);
  }
}