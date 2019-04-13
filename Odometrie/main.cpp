#include "mbed.h"

// Eléments:
#include "Encodeur.h"
#include "Odometrie.h"

// Paramètres des encodeurs:
#define encodeur_res 2000
#define encodeur_diametre 70          // en mm
#define encodeurs_entraxe 120 / 2.0f  // en mm

// Paramètre de l'odométrie:
#define update_delay_us 500  // en µs

// Encodeurs:
Encodeur encodeurG('G', encodeur_res, encodeur_diametre);
Encodeur encodeurD('D', encodeur_res, encodeur_diametre);

// Odometrie:
Odometrie odometrie(&encodeurG, &encodeurD, encodeurs_entraxe);

// Ticker:
Ticker ticker;

// Mise à jour de l'odometrie:
void update() { odometrie.update(); }

int main() {
  printf("STM32 Odometrie\r\n");
  printf("Adresses de variables: (pour STM-Studio)\r\n");
  printf(" - encodeurG.tours    = %p\r\n", encodeurG.getTours_ptr());
  printf(" - encodeurD.tours    = %p\r\n", encodeurD.getTours_ptr());
  printf(" - odometrie.X        = %p\r\n", odometrie.getX_ptr());
  printf(" - odometrie.Y        = %p\r\n", odometrie.getY_ptr());
  printf(" - odometrie.Theta    = %p\r\n", odometrie.getTheta_ptr());
  printf(" - odometrie.distance = %p\r\n", odometrie.getDistance_ptr());
  printf(" - odometrie.vitesse  = %p\r\n", odometrie.getVitesse_ptr());

  // Mesure du déplacement toutes les <update_delay_us> µs:
  ticker.attach_us(&update, update_delay_us);  // 2 kHz pour 500 us

  while (true) {
    printf("Position: %f\t%f\r\n", odometrie.getX(), odometrie.getY());
    printf("Angle:    %f\r\n", odometrie.getTheta());
    printf("Distance: %f\r\n", odometrie.getDistance());
    printf("Vitesse:  %f\r\n", odometrie.getVitesse());
    wait(1);
  }
}
