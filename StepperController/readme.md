# Stepper

Classe permettant d'utiliser un moteur pas à pas comme élément qui déplace un système linéaire ou en rotation.

Utilise un *fin de course* pour initialiser sa position.

## Utilisation

```cpp
StepperController(int steps, PinName pins[], PinName switch_pin,
                  float distance_par_tour, float pos_max,
                  bool start_null_or_max, bool inverse_dir = 0);
```
- `steps`: nombre de pas du moteur.
- `pins`: pins utilisées pour contrôler le moteur (`enable`, `direction`, `step`).
- `switch_pin` : pin utilisée par le *fin de course*.
- `distance_par_tour` : distance parcourue lorsque le moteur a réalisé un tour (unité libre : `m`, `cm`, `rad`, ...).
- `pos_max` : distance maximale que peut parcourir le moteur depuis le fin de course (avec la même unité que `distance_par_tour`).
- `start_null_or_max` : initialise la position du système à *zéro* ou à la *position maximale*.
- `inverse_dir`: direction de rotation par défaut du moteur.

### Méthodes
- `void init(int start_dist)` : initialise la position du système en se plaçant sur le *fin de course* (`start_dist` : distance à parcourir en arrière avant de se déplacer vers le *fin de course*, pour réinitialiser si le *fin de course* était déjà actif).
- `void setSpeed(long whatSpeed)` : définit la vitesse de rotation en *tours par minute*.
- `void turn(int dist)` : distance que doit réaliser le moteur pas à pas.
- `void turnAndWait(int dist)` : identique à `turn()` mais attend que le déplacement soit terminé.
- `void setPos(int pos)` : déplace le système vers la position désirée (avec l'unité de `pos` identique à celle de `distance_par_tour` lors de l'initialisation).

## Fonctionnement
- Utilise la classe `Stepper` ou `StepperDriver` (au choix en modifiant quelques paramètres) pour contrôler le moteur pas à pas.
- Initialise la position du système grâce à un fin de course.
- Le système peut être contrôlé de manière **absolue** ou **relative** (par exemple : *"va à la position 10"* (`setPos()`) ou *"avance de 10"* (`turn()`).
- Par défaut la fonction de déplacement est non bloquante, mais il est possible d'attendre que le déplacement soit fini : `turnAndWait()`.
