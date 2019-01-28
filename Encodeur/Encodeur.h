#ifndef ENCODEUR_H
#define ENCODEUR_H

#include "mbed.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Initialisation du Timer pour l'Encodeur:
void EncodeurInit(TIM_Encoder_InitTypeDef* encodeur, TIM_HandleTypeDef* timer, TIM_TypeDef* TIMx, uint32_t resolution);

class Encodeur {
 public:
  // Constructeur:
  Encodeur(char e, int resolution, int diametre);

  // Getters & Setter:
  uint16_t getCount();
  int getTotalCount();
  int getDist();  // en mm
  void updateTour(int);

  // Attributs:
  int getTours();
  int getDiametre();  // en mm
  int getResolution();
  float getTicks_par_mm();

  // Pointeur:
  int* getTours_ptr();

 private:
  int m_tours;
  int m_resolution;
  int m_diametre;  // en mm
  float m_ticks_par_mm;
  TIM_HandleTypeDef* m_timer;
};

#endif