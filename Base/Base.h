#ifndef BASE_H
#define BASE_H

#include "Asservissement.h"
#include "Moteur.h"
#include "Odometrie.h"
#include "mbed.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

class Base {
 public:
  // Constructeur:
  Base(Moteur*, Moteur*, Odometrie*, int);

  // Déplacement:
  void moveTo(float x, float y, float theta);
  void start();
  void stop();
  void forward(float);
  void backward(float);
  void turn(float);  // °

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

  // Getters:
  float getErreurDistance();
  float getErreurOrientation();

  // Setters:
  void setActualDistance();
  void setActualOrientation();

  // Moteurs:
  void forwardMoteur(float, float);
  void backwardMoteur(float, float);

 private:
  // Moteurs:
  Moteur* m_moteurG;
  Moteur* m_moteurD;
  bool m_moteurs_isEnabled;

  // Odometrie:
  Odometrie* m_odometrie;

  // Position:
  float m_x, m_y, m_theta;

  // Asservissement distance et orientation:
  Asservissement m_asservissement_distance;
  Asservissement m_asservissement_orientation;
  float m_pos_distance;
  float m_pos_orientation;
  void setDistanceTo(float);
  void setOrientationTo(float o);
  float m_max_erreur_distance, m_max_erreur_orientation;
  float m_distance_orientation_ratio;

  // PWM maximale envoyée au moteurs:
  float m_pwm_max;
  float m_pwm_dynamic;

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