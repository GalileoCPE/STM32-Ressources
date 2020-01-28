#include "mbed.h"

// Elément:
#include "Stepper.h"

// Pins du moteur pas à pas:
#define stepper_pins D4, D5, D6, D7

// Nombre de pas par tour du moteur pas à pas:
#define stepper_stepsPerRevolution 200

// Entrée du capteur fin de course:
#define switch_pin D10

Stepper stepper(stepper_stepsPerRevolution, stepper_pins);

DigitalIn limit_switch(switch_pin);

int main() {
  printf("STM32 Stepper\r\n");

  while (1) {
    // 1 tour dans le sens horaire:
    printf("Sens horaire\n\r");
    stepper.setSpeed(60);
    stepper.step(stepper_stepsPerRevolution * 5);
    wait(4);

    // 1 tour dans le sens anti-horaire:
    printf("Sens anti-horaire\n\r");
    stepper.setSpeed(100);
    stepper.step(-stepper_stepsPerRevolution * 5);
    wait(4);

    /*/ 1 tour dans le sens horaire avec stop:
    printf("Sens horaire avec stop\n\r");
    stepper.setSpeed(30);
    stepper.stepWithStop(stepper_stepsPerRevolution, &limit_switch, true);
    wait(2);
    

    // 1 tour dans le sens anti-horaire avec stop:
    printf("Sens anti-horaire avec stop\n\r");
    stepper.setSpeed(40);
    stepper.stepWithStop(-stepper_stepsPerRevolution, &limit_switch, true);
    wait(2);*/
  }
}
