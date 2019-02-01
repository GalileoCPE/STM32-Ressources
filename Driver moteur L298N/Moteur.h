#ifndef MOTEUR_H
#define MOTEUR_H

#include "mbed.h"

class Moteur {
 public:
  // Constructeur:
  Moteur(PinName pin_en, PinName pin_in1, PinName pin_in2);

  // Déplacement:
  void forward();
  void backward();
  void stop();

  // Setter:
  void setPWM(float pwm);  // entre 0 et 1

 private:
  PwmOut m_pwm;
  DigitalOut m_in1;
  DigitalOut m_in2;
};

#endif