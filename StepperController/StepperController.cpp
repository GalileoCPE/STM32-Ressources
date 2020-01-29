#include "StepperController.h"

// Constructeur:
StepperController::StepperController(int steps, PinName pins[], PinName switch_pin,
                                     float distance_par_tour, float pos_max,
                                     bool start_null_or_max, bool inverse_dir)
    : m_stepper(steps, pins[0], pins[1], pins[2], inverse_dir), m_switch(switch_pin) {
  m_convert_to_ticks = steps / distance_par_tour;
  m_pos = pos_max / 2.0f;
  m_pos_max = pos_max;
  m_start_null_or_max = start_null_or_max;

  setSpeed(10);

  m_switch.mode(PullUp);
}

// Initialisation:
bool StepperController::init(int start_dist = 0) {
  // Direction pour aller vers le fin de course:
  int dir = start_dist > 0 ? -1 : 1;

  // Tourne un petit peu en arrière:
  turnAndWait(start_dist);

  // Tourne jusqu'au fin de course:
  m_pos = (dir == 1 ? 0 : m_pos_max);  // Initialise la position pour permettre tout le déplacement
  turnWithStopAndWait(m_pos_max * dir, 0);

  // Si le fin de course ne s'est pas activé:
  if (!m_stepper.isStopBySwitch()) return 1;

  // Initialisation de la position:
  reset_pos();

  return 0;
}

// Initialisation de la position:
void StepperController::reset_pos() {
  m_pos = m_start_null_or_max == 0 ? 0 : m_pos_max;
}

// Getter:
bool StepperController::isTurning() { return !m_stepper.isStop(); }

// Setter:
void StepperController::setSpeed(long speed) { m_stepper.setSpeed(speed); }

// Tourne le moteur pour réaliser un déplacement de <dist>:
void StepperController::turn(int dist) {
  // Vérification:
  if (m_pos + dist > m_pos_max)
    dist = m_pos_max - m_pos;
  else if (m_pos + dist < 0)
    dist = -m_pos;

  // Déplacement:
  m_stepper.step(dist * m_convert_to_ticks);
  m_pos += dist;
}

// Place le moteur à une position:
void StepperController::setPos(int pos) { turn(pos - m_pos); }

// Tourne et attend la fin du déplacement:
void StepperController::turnAndWait(int dist) {
  turn(dist);

  // Attend la fin du déplacement:
  while (!m_stepper.isStop()) wait(0.1);
}

// Tourne et s'arrête, si nécessaire, au fin de course:
int StepperController::turnWithStop(int dist, bool state_to_stop) {
  // Vérification:
  if (m_pos + dist > m_pos_max)
    dist = m_pos_max - m_pos;
  else if (m_pos + dist < 0)
    dist = -m_pos;

  // Déplacement:
  m_stepper.stepWithStop(dist * m_convert_to_ticks, &m_switch, state_to_stop);

  return dist;
}

// Tourne et s'arrête, si nécessaire, au fin de course, et attend la fin du déplacement:
void StepperController::turnWithStopAndWait(int dist, bool state_to_stop) {
  dist = turnWithStop(dist, state_to_stop);

  // Attend la fin du déplacement:
  while (!m_stepper.isStop()) wait(0.1);

  // Si le fin de course ne s'est pas activé, ajoute le déplacement:
  if (!m_stepper.isStopBySwitch()) m_pos += dist;
}

// Alimente le moteur:
void StepperController::on() { m_stepper.on(); }

// Désalimente le moteur:
void StepperController::off() { m_stepper.off(); }