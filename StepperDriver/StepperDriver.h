#ifndef STEPPER_DRIVER_H
#define STEPPER_DRIVER_H
#include "mbed.h"

class StepperDriver {
 public:
  // Constructeur:
  StepperDriver(int steps, PinName pin_en, PinName pin_dir, PinName pin_step, bool inverse_dir = 0);

  // Alimente le moteur:
  void on();

  // Désalimente le moteur:
  void off();

  // Setter:
  void setSpeed(long whatSpeed);

  // Getter:
  bool isStop();
  bool isStopBySwitch();

  // Rotation:
  void step(int steps);
  void stepWithStop(int steps, DigitalIn* limit_switch, bool state_to_stop);

 private:
  void step_init(int steps);
  void update();
  void updateWithStop();
  void stepMotor(int this_step);

  // Variables du déplacement:
  bool m_direction, m_inverse_dir;
  int m_steps, m_step_counter, m_steps_left;
  unsigned long m_step_delay_us;  // Délais entre pas, en µs
  bool m_inProgress;
  bool m_stop_by_switch;

  // Pins du moteur:
  DigitalOut m_pin_en;
  DigitalOut m_pin_dir;
  DigitalOut m_pin_step;

  // Capteur fin de course:
  DigitalIn* m_limit_switch;

  // Etat du capteur fin de course pour arrêter le déplacement:
  bool m_switch_state_stop;

  // Ticker:
  Ticker m_ticker;
};

#endif