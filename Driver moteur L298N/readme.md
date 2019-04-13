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
- `setPWM_max(float pwm)` : définit le rapport cyclique maximale qui peut être utilisé avec la méthode `turn()`
- `stop()` : arrête le moteur en mettant la sortie `pin_en` à `0`
- `forward()` : pour alimenter le moteur dans un sens
- `backward()` : pour alimenter le moteur dans l'autre sens
- `turn(float pwm)` : alimente le moteur pour aller en avant (`pwm > 0`) ou en arrière (`pwm < 0`), (!!: `pwm` est adaptée pour ne pas dépasser la valeur définie par `setPWM_max()`)


## Informations utiles
- Toujours vérifier qu'une masse est commune entre la carte et le driver.
- Ne pas changer **instantanément** le sens du moteur, sinon cela génère un pic de courant qui peut **détruire** (voire exploser) le driver. Ainsi, il est préférable d'**arrêter** l'alimentation fournit au moteur (`stop()`), puis d'**attendre** (`wait()`) avant de le **redémarrer** dans l'autre sens.
- La période de la PWM est déterminée dans le constructeur et peut donc être modifiée. (Actuellement : période = `100 µs` soit une fréquence de `10 kHz`)
- Par défaut, le rapport cyclique qui peut être envoyé grâce à la méthode `turn()` est limité au maximum à `0.5`, pour ainsi éviter d'alimenter le moteur par des valeurs trop grandes. La méthode `setPWM_max()` permet de modifier cette limite.
