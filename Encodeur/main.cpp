#include "mbed.h"

// Elément:
#include "Encodeur.h"

// Paramètres des encodeurs:
#define encodeur_res 2000
#define encodeur_diametre 100  // en mm

// Encodeurs:
Encodeur encodeurG('G', encodeur_res, encodeur_diametre);
Encodeur encodeurD('D', encodeur_res, encodeur_diametre);

// LED:
DigitalOut led(LED1);

int main() {
  printf("STM32 Encodeur\r\n");
  printf("Adresses de variables: (pour STM-Studio)"
  printf(" - encodeurG.tours = %p\r\n", encodeurG.getTours_ptr());
  printf(" - encodeurD.tours = %p\r\n", encodeurD.getTours_ptr());

  while (true) {
    uint16_t countG = encodeurG.getCount();
    int toursG = encodeurG.getTours();
    int distG = encodeurG.getDist();

    uint16_t countD = encodeurD.getCount();
    int toursD = encodeurD.getTours();
    int distD = encodeurD.getDist();

    printf("G: %d\t%d  -> %d mm\r\n", countG, toursG, distG);
    printf("D: %d\t%d  -> %d mm\r\n\n", countD, toursD, distD);

    // Allume la LED si le nombre de tours est impair:
    led = toursD % 2;

    wait(0.5);
  }
}