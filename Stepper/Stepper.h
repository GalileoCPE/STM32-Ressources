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
  void stepWithStop(int steps, DigitalIn* limit_switch, bool state_to_stop);

 private:
  void step_init(int steps);
  void update();
  void updateWithStop();
  void stepMotor(int this_step);

  // Variables du déplacement:
  int m_direction;
  int m_steps, m_step_counter, m_steps_left;
  unsigned long m_step_delay_us;  // Délais entre pas, en µs

  // Pins du moteur:
  DigitalOut m_pin_1;
  DigitalOut m_pin_2;
  DigitalOut m_pin_3;
  DigitalOut m_pin_4;

  // Capteur fin de course:
  DigitalIn* m_limit_switch;

  // Etat du capteur fin de course pour arrêter le déplacement:
  bool m_switch_state_stop;

  // Ticker:
  Ticker m_ticker;
};

#endif