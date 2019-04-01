# Stepper

Classe permettant d'utiliser un moteur pas à pas.

## Utilisation

```cpp
Stepper(int steps, PinName pin_1, PinName pin_2, PinName pin_3, PinName pin_4);
```
- `steps`: nombre de pas du moteur
- `pin_N`: pins utilisées pour brancher le moteur (`1-2`, `3-4` correspondent aux pins d'une même bobine) 

### Méthodes
- `void setSpeed(long whatSpeed)` : défini la vitesse de rotation en tour par minute
- `void step(int steps)` : rotation de `steps` pas (`steps` négatif pour tourner dans l'autre sens)

## Fonctionnement
- Produit les impulsions pour faire tourner le moteur pas à pas d'un certain nombre de pas.
- Chaque pas se produit à intervalle régulier, dont la durée dépend de la vitesse paramétrée.

## Informations utiles
- Classe grandement inspirée de la classe [`Servo`](https://github.com/esp8266/Arduino/tree/master/libraries/Servo/src) utilisée pour Arduino.
- **!!!** : Ne pas brancher directement le moteur pas à pas sur la carte STM32. Utiliser un **driver moteur** pour cela, et brancher les pins de la même manière qu'ils auraient été sur le moteur (c'est-à-dire dans le même ordre).
- Utilise la librairie [Mbed OS 5](https://os.mbed.com/) pour configurer facilement le microcontrôleur et utiliser la classe `Ticker` pour exécuter une fonction à intervalle régulié.