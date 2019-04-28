#include "mbed.h"

// Eléments:
#include "Base.h"
#include "Encodeur.h"
#include "Moteur.h"
#include "Odometrie.h"

/*** Paramètres ***/

// Pins des moteurs:
#define pins_moteurG_enA_in1_in2 D7, D14, D15
#define pins_moteurD_enB_in1_in2 D8, D11, D12

// Paramètres des encodeurs:
#define encodeur_res 2000
#define encodeur_diametre 70          // en mm
#define encodeurs_entraxe 120 / 2.0f  // en mm

// Paramètre de l'odometrie et asservissement:
#define update_delay_us 500  // en µs

/*** Création des objets ***/

// Moteurs:
Moteur moteurG(pins_moteurG_enA_in1_in2);
Moteur moteurD(pins_moteurD_enB_in1_in2);

// Encodeurs:
Encodeur encodeurG('G', encodeur_res, encodeur_diametre);
Encodeur encodeurD('D', encodeur_res, encodeur_diametre);

// Odometrie:
Odometrie odometrie(&encodeurG, &encodeurD, encodeurs_entraxe);

// Base:
Base base(&moteurG, &moteurD, &odometrie, update_delay_us);

int main() {
  printf("STM32 Base\r\n");
  printf("Adresses de variables: (pour STM-Studio)\r\n");
  printf(" - encodeurG.tours   = %p\r\n", encodeurG.getTours_ptr());
  printf(" - encodeurD.tours   = %p\r\n", encodeurD.getTours_ptr());
  printf(" - odometrie.X       = %p\r\n", odometrie.getX_ptr());
  printf(" - odometrie.Y       = %p\r\n", odometrie.getY_ptr());
  printf(" - odometrie.Theta   = %p\r\n", odometrie.getTheta_ptr());
  printf(" - base.erreur_distance    = %p\r\n", base.getErreur_distance_ptr());
  printf(" - base.erreur_orientation = %p\r\n", base.getErreur_orientation_ptr());
  printf(" - base.pwm_distance       = %p\r\n", base.getPID_PWM_distance_ptr());
  printf(" - base.pwm_orientation    = %p\r\n", base.getPID_PWM_orientation_ptr());
  printf(" - base.pwm_gauche   = %p\r\n", base.getPID_PWM_gauche_ptr());
  printf(" - base.pwm_droite   = %p\r\n", base.getPID_PWM_droite_ptr());

  // PID:
  base.setPID_distance(0.1, 0, 1);
  base.setPID_orientation(3, 0, 1);

  // Haut:
  base.setOrientationTo(0.0f);
  wait(3);
  base.setDistanceTo(500);
  wait(3);

  // Droite:
  base.setOrientationTo(90.0f);
  wait(3);
  base.setDistanceTo(1000);
  wait(3);

  // Bas:
  base.setOrientationTo(180.0f);
  wait(3);
  base.setDistanceTo(1500);
  wait(3);

  // Gauche:
  base.setOrientationTo(270.0f);
  wait(3);
  base.setDistanceTo(2000);
  wait(3);

  // Fin
  base.setOrientationTo(360);
  wait(3);
  base.setOrientationTo(0);
  wait(3);

  while (true) {
    printf("Position: %f\t%f\r\n", odometrie.getX(), odometrie.getY());
    printf("Angle: %f\r\n", odometrie.getTheta());

    wait(1);
  }
}
