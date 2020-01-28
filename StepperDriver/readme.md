# Stepper

Classe permettant d'utiliser un moteur pas à pas avec un *driver*.

## Utilisation

```cpp
StepperDriver::StepperDriver(int steps, PinName pin_en, PinName pin_dir, PinName pin_step, bool inverse_dir = 0);
```
- `steps`: nombre de pas du moteur
- `pin_N`: pins utilisées pour contrôler le moteur (`enable`, `direction`, `step`)
- `inverse_dir`: direction de rotation par défaut du moteur

### Méthodes
- `void setSpeed(long whatSpeed)` : définit la vitesse de rotation en tours par minute
- `void step(int steps)` : rotation de `steps` pas (`steps` négatif pour tourner dans l'autre sens)
- `void stepWithStop(int steps, DigitalIn* limit_switch, bool state_to_stop)` : rotation de `steps` pas, mais s'arrête si un *interrupteur* est à l'état `state_to_stop`

## Fonctionnement
- Produit les impulsions pour contrôler le *driver* qui alimenter le moteur pas à pas.
- Chaque pas se produit à intervalle régulier, dont la durée dépend de la vitesse paramétrée.
- Peut arrêter la rotation d'un moteur lorsqu'un interrupteur est activé, pour par exemple initialiser sa position.

## Informations utiles
- Classe grandement inspirée de la classe [`Stepper`](https://github.com/arduino-libraries/Stepper/tree/master/src) utilisée pour Arduino.
- **!!!** : Ne pas brancher directement le moteur pas à pas sur la carte STM32. Utiliser un **driver moteur** pour cela, et brancher les pins de la même manière qu'ils auraient été sur le moteur (c'est-à-dire dans le même ordre) (+ ne pas oublier de relier les **masses** entre la STM32 et le driver).
- Utilise la librairie [Mbed OS 5](https://os.mbed.com/) pour configurer facilement le microcontrôleur et utiliser la classe `Ticker` pour exécuter une fonction à intervalle régulié.
