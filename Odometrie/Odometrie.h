#ifndef ODOMETRIE_H
#define ODOMETRIE_H

#include "Encodeur.h"
#include "mbed.h"

class Odometrie {
 public:
  // Constructeur:
  Odometrie(Encodeur* encodeurG, Encodeur* encodeurD, float entraxe, int update_delay_us);

  void update();

  // Getters:
  float getX();
  float getY();
  float getTheta();

  // Pointeurs:
  float* getX_ptr();
  float* getY_ptr();
  float* getTheta_ptr();

 private:
  // Position et orientation:
  float m_L, m_X, m_Y, m_Theta;

  // Encodeurs:
  Encodeur* m_encodeurG;
  Encodeur* m_encodeurD;
  float m_ticks_par_mm, m_entraxe_ticks;

  int m_prev_encodeurG_count, m_prev_encodeurD_count;

  // Ticker:
  Ticker m_ticker;
};

#endif