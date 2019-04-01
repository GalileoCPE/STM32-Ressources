#include "mbed.h"

// Elément:
#include "Stepper.h"

// Pins du moteur pas à pas:
#define stepper_pins D4, D5, D6, D7

// Nombre de pas par tour du moteur pas à pas:
#define stepper_stepsPerRevolution 200

Stepper stepper(stepper_stepsPerRevolution, stepper_pins);

int main() {
  printf("STM32 Stepper\r\n");

  while (1) {
    // 1 tour dans le sens horaire:
    printf("Sens horaire\n\r");
    stepper.setSpeed(60);
    stepper.step(stepper_stepsPerRevolution);
    wait(2);

    // 1 tour dans le sens anti-horaire:
    printf("Sens anti-horaire\n\r");
    stepper.setSpeed(100);
    stepper.step(-stepper_stepsPerRevolution);
    wait(2);
  }
}
