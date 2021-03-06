#include "Stepper.h"

// Constructeur:
Stepper::Stepper(int steps, PinName pin_1, PinName pin_2, PinName pin_3, PinName pin_4)
    : m_pin_1(pin_1, 0), m_pin_2(pin_2, 0), m_pin_3(pin_3, 0), m_pin_4(pin_4, 0) {
  m_steps = steps;
  m_direction = 0;
  m_step_counter = 0;
}

// Setter:
void Stepper::setSpeed(long speed) {
  m_step_delay_us = 60L * 1000L * 1000L / m_steps / speed;
}

// Etape d'initilisation pour un déplacement:
void Stepper::step_init(int steps_to_move) {
  m_steps_left = abs(steps_to_move);

  // Direction:
  if (steps_to_move > 0) m_direction = 1;
  if (steps_to_move < 0) m_direction = 0;

  // Arrête le déplacement en cours (s'il y en un 1):
  m_ticker.detach();
}

// Démarre le déplacement du moteur de <steps_to_move> pas, avec Ticker:
void Stepper::step(int steps_to_move) {
  // Initialisation du déplacement:
  step_init(steps_to_move);

  // Démarre le déplacement demandé:
  m_ticker.attach_us(callback(this, &Stepper::update), m_step_delay_us);
}

// Etape de déplacement du moteur (exécuté à un rythme régulié):
void Stepper::update() {
  // Compte le nombre de pas en fonction de la direction:
  if (m_direction == 1) {
    m_step_counter++;
    if (m_step_counter == m_steps) m_step_counter = 0;
  } else {
    if (m_step_counter == 0) m_step_counter = m_steps;
    m_step_counter--;
  }

  m_steps_left--;

  // Déplace le moteur d'un pas (selon les étapes 0, 1, 2 ou 3):
  stepMotor(m_step_counter % 4);

  // Si fin du déplacement:
  if (m_steps_left == 0) m_ticker.detach();
}

// Démarre le déplacement du moteur de <steps_to_move> pas, avec Ticker et s'arrête si fin de course activé:
void Stepper::stepWithStop(int steps_to_move, DigitalIn* limit_switch, bool state_to_stop) {
  // Initialisation du déplacement:
  step_init(steps_to_move);

  // Entrée du capteur de fin de course:
  m_limit_switch = limit_switch;

  // Etat pour arrêter le déplacement:
  m_switch_state_stop = state_to_stop;

  // Démarre le déplacement demandé:
  m_ticker.attach_us(callback(this, &Stepper::updateWithStop), m_step_delay_us);
}

// Mise à jour du déplacement avec arrêt:
void Stepper::updateWithStop() {
  // Vérifie l'état du capteur de fin de course:
  if (*m_limit_switch == m_switch_state_stop) {
    // Arrête le déplacement en cours:
    m_ticker.detach();
  } else {
    // Etape de déplacement du moteur:
    update();
  }
}

// Déplace le moteur en avant ou en arrière d'un pas:
void Stepper::stepMotor(int thisStep) {
  switch (thisStep) {
    case 0:  // 1010
      m_pin_1 = 1;
      m_pin_2 = 0;
      m_pin_3 = 1;
      m_pin_4 = 0;
      break;

    case 1:  // 0110
      m_pin_1 = 0;
      m_pin_2 = 1;
      m_pin_3 = 1;
      m_pin_4 = 0;
      break;

    case 2:  // 0101
      m_pin_1 = 0;
      m_pin_2 = 1;
      m_pin_3 = 0;
      m_pin_4 = 1;
      break;

    case 3:  // 1001
      m_pin_1 = 1;
      m_pin_2 = 0;
      m_pin_3 = 0;
      m_pin_4 = 1;
      break;
  }
}
