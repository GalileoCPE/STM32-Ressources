#include "StepperDriver.h"

// Constructeur:
StepperDriver::StepperDriver(int steps, PinName pin_en, PinName pin_dir, PinName pin_step, bool inverse_dir)
    : m_pin_en(pin_en, 0), m_pin_dir(pin_dir, 0), m_pin_step(pin_step, 0) {
  m_steps = steps;
  m_direction = 0;
  m_inverse_dir = inverse_dir;
  m_step_counter = 0;
  m_inProgress = 0;
  m_stop_by_switch = 0;

  on();
}

// Alimente le moteur:
void StepperDriver::on() { m_pin_en = 0; }

// Désalimente le moteur:
void StepperDriver::off() { m_pin_en = 1; }

// Setter:
void StepperDriver::setSpeed(long speed) {
  m_step_delay_us = 60L * 1000L * 1000L / m_steps / speed;
}

// Getter:
bool StepperDriver::isStop() { return !m_inProgress; }
bool StepperDriver::isStopBySwitch() { return m_stop_by_switch; }

// Etape d'initilisation pour un déplacement:
void StepperDriver::step_init(int steps_to_move) {
  m_steps_left = abs(steps_to_move) * 2;

  // Direction:
  if (steps_to_move > 0) m_direction = m_inverse_dir - 1;
  if (steps_to_move < 0) m_direction = m_inverse_dir - 0;
  m_pin_dir = m_direction;

  // Moteur en fonctionnement:
  m_inProgress = 1;
  m_stop_by_switch = 0;

  // Arrête le déplacement en cours (s'il y en un 1):
  m_ticker.detach();
}

// Démarre le déplacement du moteur de <steps_to_move> pas, avec Ticker:
void StepperDriver::step(int steps_to_move) {
  // Vérification:
  if (steps_to_move == 0) return;

  // Initialisation du déplacement:
  step_init(steps_to_move);

  // Démarre le déplacement demandé:
  m_ticker.attach_us(callback(this, &StepperDriver::update), m_step_delay_us);
}

// Etape de déplacement du moteur (exécuté à un rythme régulié):
void StepperDriver::update() {
  // Compte le nombre de pas en fonction de la direction:
  if (m_direction == 1) {
    m_step_counter++;
    if (m_step_counter == m_steps) m_step_counter = 0;
  } else {
    if (m_step_counter == 0) m_step_counter = m_steps;
    m_step_counter--;
  }

  m_steps_left--;

  // Déplace le moteur d'un pas (selon les étapes 0 ou 1):
  stepMotor(m_step_counter % 2);

  // Si fin du déplacement:
  if (m_steps_left == 0) {
    m_inProgress = 0;
    m_ticker.detach();
  }
}

// Démarre le déplacement du moteur de <steps_to_move> pas, avec Ticker et s'arrête si fin de course activé:
void StepperDriver::stepWithStop(int steps_to_move, DigitalIn* limit_switch, bool state_to_stop) {
  // Vérification:
  if (steps_to_move == 0) return;

  // Initialisation du déplacement:
  step_init(steps_to_move);

  // Entrée du capteur de fin de course:
  m_limit_switch = limit_switch;

  // Etat pour arrêter le déplacement:
  m_switch_state_stop = state_to_stop;

  // Démarre le déplacement demandé:
  m_ticker.attach_us(callback(this, &StepperDriver::updateWithStop), m_step_delay_us);
}

// Mise à jour du déplacement avec arrêt:
void StepperDriver::updateWithStop() {
  // Vérifie l'état du capteur de fin de course:
  if (*m_limit_switch == m_switch_state_stop) {
    // Arrête le déplacement en cours:
    m_ticker.detach();

    // Moteur à l'arrêt:
    m_inProgress = 0;

    // Arrêté par fin de course:
    m_stop_by_switch = 1;
  } else {
    // Etape de déplacement du moteur:
    update();
  }
}

// Déplace le moteur en avant ou en arrière d'un pas:
void StepperDriver::stepMotor(int thisStep) {
  switch (thisStep) {
    case 0:  // 0
      m_pin_step = 0;
      break;

    case 1:  // 1
      m_pin_step = 1;
      break;
  }
}
