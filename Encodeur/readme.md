# Encodeur

Classe permettant de gérer les impulsions émises par un encodeur.

Détermine la position de façon *hardware*, et compte le nombre de tours réalisé pour en déduire la distance parcourue.

## Utilisation

Dès la construction de l'objet, celui-ci fonctionne automatiquement.

Ce programme est configuré pour paramétrer **deux encodeurs** afin d'asservir le déplacement d'un robot.

### Constructeur :
   ```c
   Encodeur encodeurG(char e, int resolution, int diametre);
   ```
- `e` : encodeur droit `'D'` ou gauche `'G'`
- `resolution` : résolution de l'encodeur (nombre d'impulsions en 1 tour)
- `diametre` : diamètre de la roue fixée sur l'encodeur

### Méthodes :
  - `getCount()` : renvoie la valeur contenue dans le Timer utilisé par l'encodeur (`TIMx_CNT`)
  - `getTours()` : renvoie le nombre de tours réalisé par l'encodeur
  - `getDist()` : renvoie la distance en mm, depuis le démarrage, en fonction du diamètre de la roue

## Fonctionnement
- Utilise un Timer en `mode encodeur`.
- Le Timer recupère les **deux signaux** de l'encodeur, qui **incrémente** ou **décrémente** le compteur à chaque front (*montant* ou *descendant*) de chacun des signaux (le compteur compte alors **4** fois plus d'implusions que le nombre inscrit sur l'encodeur)
- Le Timer tourne en boucle entre `0` et `4 * resolution - 1`.
- Une interruption `TIMx_IRQHandler` est déclenchée dès que le Timer est égale à `0` : permet de compter le nombre de tours réaliser par l'encodeur.


## Détails des fichiers
  - `main.cpp` : exemple d'utilisation avec deux encodeurs
  - `Encodeur.h`, `Encodeur.cpp` : Objet Encodeur
  - `Nucleo/` : contient les configurations des GPIOs en fonction du Timer pour la carte utilisée

## Informations utiles
- Utilise la librairie [Mbed OS 5](https://os.mbed.com/) seulement pour configurer facilement le microcontrôleur.
- Testé et programmé pour une carte `NUCLEO-F411RE`.
- Les Timers **3** et **4** du microcontrôlleur sont utilisés.
- **! ! !** : les objets Encodeur doivent être **globaux**, et posséder le **même nom** que ceux utilisés dans les **fonctions d'interruptions** `TIMx_IRQHandler`.
- **Pins** d'entrée des Timers :
  - `Timer 3` : `PB4` `PB5`
  - `Timer 4` : `PB6` `PB7`
- Inspiré par ce [programme](https://os.mbed.com/users/gregeric/code/Nucleo_Hello_Encoder/).