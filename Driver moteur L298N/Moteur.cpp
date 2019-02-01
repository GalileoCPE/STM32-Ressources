#include "Moteur.h"

Moteur::Moteur(PinName pin_en, PinName pin_in1, PinName pin_in2)
    : m_pwm(pin_en), m_in1(pin_in1, 0), m_in2(pin_in2, 0) {

  m_pwm.period_us(100.0f);  // Fréquence = 10 kHz pour 100 µs

}

// Setter:
void Moteur::setPWM(float pwm) { m_pwm = pwm; }


/*** Déplacement ***/

// Avant:
void Moteur::forward() {
  m_in1 = 1;
  m_in2 = 0;
}

// Arrière:
void Moteur::backward() {
  m_in1 = 0;
  m_in2 = 1;
}

// Arrêt:
void Moteur::stop() {
  m_pwm.write(0.0f);  // Duty cycle
}
