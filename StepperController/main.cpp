#include "mbed.h"

// Elément:
#include "StepperController.h"

// Pins du moteur pas à pas:
#define stepper_en_dir_step (PinName[]) { D8, D6, D7 }

// Nombre de pas par tour du moteur pas à pas:
#define stepper_stepsPerRevolution 200

// Distance/angle parcouru par l'élément fixé sur le moteur:
#define distance_par_tour 10.0f
#define distance_max      30.0f
#define distance_init     2.0f  // Distance à parcourir à l'opposer du switch pour initialiser

// Initialise à la position minimale:
#define start_null 0

// Entrée du capteur fin de course:
#define switch_pin USER_BUTTON

StepperController stepper(stepper_stepsPerRevolution, stepper_en_dir_step, switch_pin, distance_par_tour, distance_max, start_null);

int main() {
  printf("STM32 Stepper Controller\r\n");

  printf("Initialisation...\r\n");
  stepper.init(distance_init);

  while (1) {
    // Avance sur toute la longueur:
    printf("Avance\n\r");
    stepper.setSpeed(60);
    stepper.turn(distance_max);
    wait(6);

    // Recule sur toute la longueur:
    printf("Recule\n\r");
    stepper.setSpeed(100);
    stepper.turn(-distance_max);
    wait(6);

    // Déplace à une position:
    printf("Position\n\r");
    stepper.turn(-12.0f);
    wait(6);

    // Avance un peu:
    printf("Avance\n\r");
    stepper.turn(2.0f);
    wait(6);
  }
}
