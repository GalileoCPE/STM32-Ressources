#ifndef BASE_H
#define BASE_H

#include "Asservissement.h"
#include "Moteur.h"
#include "Odometrie.h"
#include "mbed.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Base {
 public:
  // Constructeur:
  Base(Moteur*, Moteur*, Odometrie*, int);

  // Déplacement:
  void setDistanceTo(float);
  void setOrientationTo(float o);

  // PID:
  void setPID_distance(float P, float I, float D);
  void setPID_orientation(float P, float I, float D);

  // Pointeurs:
  float* getErreur_distance_ptr();
  float* getErreur_orientation_ptr();
  float* getPID_PWM_distance_ptr();
  float* getPID_PWM_orientation_ptr();
  float* getPID_PWM_gauche_ptr();
  float* getPID_PWM_droite_ptr();

 private:
  // Moteurs:
  Moteur* m_moteurG;
  Moteur* m_moteurD;

  // Odometrie:
  Odometrie* m_odometrie;

  // Asservissement distance et orientation:
  Asservissement m_asservissement_distance;
  Asservissement m_asservissement_orientation;

  // PWM maximale envoyée au moteurs:
  float m_pwm_max;

  // Debug:
  float m_erreur_distance, m_erreur_orientation;
  float m_pwm_gauche, m_pwm_droite;
  float m_pwm_distance, m_pwm_orientation;

  // Mise à jour de la position:
  void update();

  // Ticker:
  Ticker m_ticker;
};

#endif