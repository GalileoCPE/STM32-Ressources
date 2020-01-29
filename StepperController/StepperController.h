#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H

#include "StepperDriver.h"
#include "mbed.h"

class StepperController {
 public:
  // Constructeur:
  StepperController(int steps, PinName pins[], PinName switch_pin,
                    float distance_par_tour, float distance_max,
                    bool start_null_or_max, bool inverse_dir = 0);

  // Initialisation de la position:
  bool init(int start_dist);

  // Getter:
  bool isTurning();

  // Définit la vitesse:
  void setSpeed(long speed);

  // Rotation:
  void turn(int dist);
  void steps();

  // Rotation avec arrêt:
  int turnWithStop(int dist, bool state_to_stop);

  // Attend la fin du déplacement:
  void turnAndWait(int dist);
  void turnWithStopAndWait(int dist, bool state_to_stop);

  // Position:
  void setPos(int pos);

  // Alimente le moteur:
  void on();

  // Désalimente le moteur:
  void off();

 private:
  StepperDriver m_stepper;
  DigitalIn m_switch;

  float m_pos, m_pos_max;
  float m_convert_to_ticks;

  bool m_start_null_or_max;

  void reset_pos();
};

#endif