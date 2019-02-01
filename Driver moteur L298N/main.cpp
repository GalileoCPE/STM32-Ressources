#include "mbed.h"

// Elément:
#include "Moteur.h"

// Pins des moteurs
#define pin_moteurG_enA D9
#define pin_moteurG_in1 D10
#define pin_moteurG_in2 D11

#define pin_moteurD_enB D6
#define pin_moteurD_in3 D7
#define pin_moteurD_in4 D8

// Moteurs
Moteur moteurG(pin_moteurG_enA, pin_moteurG_in1, pin_moteurG_in2);
Moteur moteurD(pin_moteurD_enB, pin_moteurD_in3, pin_moteurD_in4);

int main() {
  printf("STM32 Moteur\r\n");

  while (true) {
    printf("Marche avant...\r\n");
    moteurG.forward();
    moteurG.setPWM(0.1f);
    moteurD.forward();
    moteurD.setPWM(0.1f);
    wait(4);

    moteurG.stop();
    moteurD.stop();
    printf("Stop\r\n");
    wait(2);

    printf("Marche arrière...\r\n");
    moteurG.backward();
    moteurG.setPWM(0.1f);
    moteurD.backward();
    moteurD.setPWM(0.1f);
    wait(4);

    moteurG.stop();
    moteurD.stop();
    printf("Stop\r\n");
    wait(2);
  }
}