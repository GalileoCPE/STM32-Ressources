#ifndef STEPPER_H
#define STEPPER_H

#include "mbed.h"

class Stepper {
 public:
  // Constructeur:
  Stepper(int steps, PinName pin_1, PinName pin_2, PinName pin_3, PinName pin_4);

  // Setter:
  void setSpeed(long whatSpeed);

  // Rotation:
  void step(int steps);

 private:
  void stepMotor(int this_step);
  void update();

  // Variables du déplacement:
  int m_direction;
  int m_steps, m_step_counter, m_steps_left;
  unsigned long m_step_delay_us;  // Délais entre pas, en µs

  // Pins du moteur:
  DigitalOut m_pin_1;
  DigitalOut m_pin_2;
  DigitalOut m_pin_3;
  DigitalOut m_pin_4;

  // Ticker:
  Ticker m_ticker;
};

#endif