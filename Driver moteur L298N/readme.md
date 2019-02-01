# Driveur Moteur L298N

Classe permettant de contrôler un moteur branché sur un driver L298N.

## Utilisation

### Constructeur
```c
Moteur moteur(PinName pin_en, PinName pin_in1, PinName pin_in2);
```

- `pin_en`, `pin_in1`, `pin_in2` : pins de la carte contrôlant le pont H du driver (`in1` et `in2`), et son activation (`en`)
- `pin_en`: doit être une sortie `PWM`

### Méthodes

- `setPWM(float pwm)` : alimente le moteur avec un rapport cyclique de `pwm` (entre `0` et `1`)
- `stop()` : arrête le moteur en mettant la sortie `pin_en` à `0`
- `forward()` : pour alimenter le moteur dans un sens
- `backward()` : pour alimenter le moteur dans l'autre sens


## Informations utiles
- Toujours vérifier qu'une masse est commune entre la carte et le driver.
- Ne pas changer **instantanément** le sens du moteur, sinon cela génère un pic de courant qui peut **détruire** (voire exploser) le driver. Ainsi, il est préférable d'**arrêter** l'alimentation fournit au moteur (`stop()`), puis d'**attendre** (`wait()`) avant de le **redémarrer** dans l'autre sens.
- La période de la PWM est déterminée dans le constructeur et peut donc être modifiée. (Actuellement : période = `100 µs` soit une fréquence de `10 kHz`)
