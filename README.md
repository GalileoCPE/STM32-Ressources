# Ressources STM32
Ensemble de programmes pour utiliser des capteurs et actionneurs avec une carte STM32.

## Capteurs :
  - [Encodeur](./Encodeur) : détermine l'orientation et le nombre de tours réalisé par un encodeur (utile pour l'asservissement d'un moteur)
  - [Ultrason](./Ultrason) : todo


## Actionneurs :
  - [Driver moteur L298N](./Driver%20moteur%20L298N) : contrôle d'un moteur alimenté avec un driver L298N
  - [Stepper](./Stepper) : contrôle d'un moteur pas à pas
  - [Servomoteur](./Servomoteur) : todo


## Autres :
  - [Odométrie](./Odometrie) : détermine la position et l'orientation d'une base, à l'aide de deux encodeurs
  - [Asservissement](./Asservissement) : calcul l'erreur entre une valeur désirée et la valeur actuelle
  - [Base](./Base) : pour une base composée de 2 [moteurs](./Driver%20moteur%20L298N) et de 2 [encodeurs](./Encodeur), détermine, à partir de l'[odométrie](./Odometrie), comment alimenter les moteurs pour atteindre une position désirée, grâce à l'[asservissement](./Asservissement)