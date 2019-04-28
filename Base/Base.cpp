#include "Base.h"

// Constructeur:
Base::Base(Moteur* moteurG, Moteur* moteurD, Odometrie* odometrie, int update_delay_us)
    : m_asservissement_distance(1, 1, 1), m_asservissement_orientation(1, 1, 1) {
  m_moteurG = moteurG;
  m_moteurD = moteurD;

  // Odométrie:
  m_odometrie = odometrie;

  // Asservissement:
  m_moteurG->setPWM_max(0.6);
  m_moteurD->setPWM_max(0.6);
  m_moteurG->setOffset(0.1);
  m_moteurD->setOffset(0.1);
  m_pwm_dynamic = 0.5f;  // = 0.6 - 0.1
  
  // Répartition PWM entre distance et orientation:
  m_distance_theta_ratio = 0.5f; // 50% -> distance, 50% -> orientation

  // Mesure du déplacement toutes les <update_delay_us> µs:
  m_ticker.attach_us(callback(this, &Base::update), update_delay_us);  // 2 kHz pour 500 us
}

// Setters:
void Base::setDistanceTo(float d) { m_asservissement_distance.toValue(d); }
void Base::setOrientationTo(float o) {
  m_asservissement_orientation.toValue(M_PI * o / 180.0f);
}

// PID:
void Base::setPID_distance(float P, float I, float D) {
  m_asservissement_distance.setPID(P, I, D);
}
void Base::setPID_orientation(float P, float I, float D) {
  m_asservissement_orientation.setPID(P, I, D);
}

// Getters:
float* Base::getErreur_distance_ptr() { return &m_erreur_distance; }
float* Base::getErreur_orientation_ptr() { return &m_erreur_orientation; }
float* Base::getPID_PWM_distance_ptr() { return &m_pwm_distance; }
float* Base::getPID_PWM_orientation_ptr() { return &m_pwm_orientation; }
float* Base::getPID_PWM_gauche_ptr() { return &m_pwm_gauche; }
float* Base::getPID_PWM_droite_ptr() { return &m_pwm_droite; }

// Renvoie le signe de la valeur:
template <typename T>
int sign(T val) {
  return (T(0) < val) - (val < T(0));
}

// Mise à jour de l'odometrie et de l'asservissement:
void Base::update() {
  // Mise à jour de la position:
  m_odometrie->update();

  // Calcul de l'erreur de distance:
  float distance = m_odometrie->getRealDistance();
  float erreur_distance = m_asservissement_distance.computeError(distance);

  // Calcul de l'erreur d'orientation:
  float theta = m_odometrie->getTheta();
  float erreur_theta = m_asservissement_orientation.computeError(theta);

  // Correction de l'erreur:
  if (abs(erreur_distance) > 300) erreur_distance = 300 * sign(erreur_distance);
  if (abs(erreur_theta) > 3) erreur_theta = 3 * sign(erreur_theta);

  // PWM correspondant à la distance et à l'orientation:
  float pwm_distance = (erreur_distance / 300.0f) * m_distance_theta_ratio;
  float pwm_theta = (erreur_theta / 3.0f) * (1.0f - m_distance_theta_ratio);

  // PWM à envoyer aux moteurs:
  float pwm_droite = (pwm_distance + pwm_theta) * m_pwm_dynamic;
  float pwm_gauche = (pwm_distance - pwm_theta) * m_pwm_dynamic;

  // Commande des moteurs:
  m_moteurD->turn(pwm_droite);
  m_moteurG->turn(pwm_gauche);

  // Sauvegarde / Debug:
  m_pwm_distance = pwm_distance;
  m_pwm_orientation = pwm_theta;
  m_erreur_distance = erreur_distance;
  m_erreur_orientation = erreur_theta;
  m_pwm_droite = pwm_droite;
  m_pwm_gauche = pwm_gauche;
}