# Odométrie

Classe permettant de calculer la position et l'orientation d'une base à partir de 2 encodeurs.


## Utilisation
Utilise les données de **2 encodeurs** pour déterminer la position et la rotation d'une base (!!! : ne pas oublier d'importer la classe [`Encodeur`](../Encodeur))

### Constructeur
```c
Odometrie odometrie(Encodeur* encodeurG, Encodeur* encodeurD, float entraxe, int update_delay_us)
```

- `encodeurG`, `encodeurD` : pointeurs des encodeurs utilisés pour l'odométrie
- `entraxe` : distance/2 séparant les deux encodeurs
- `update_delay_us` : durée (en µs) pour déclencher la méthode `update()` à intervalles réguliers

### Méthodes
- `update()` : effectue la mise à jour de la position et de l'orientation
- `getX()`, `getY()`, `getTheta()` : pour récupèrer les positions X, Y et l'angle calculés par l'odométrie


## Fonctionnement

- La fonction `update()` se déclenche à intervalle régulier toutes les `update_delay_us` µs.
- Cette fonction calcule le *petit déplacement* réalisé depuis le dernier déclenchement.
- L'ajout progressif de tous ces *petits déplacements* permet d'en déduire la position et l'orientation des encodeurs, et donc de la base.


## Informations utiles
- Algorithme de l'odométrie trouvé sur le *Wiki* du *ClubElek* : [Asservissement et pilotage de robot autonome](https://wiki.clubelek.fr/articles:asservissement_et_pilotage_de_robot_autonome)
- Pour obtenir un résultat intéressant: les encodeurs doivent être placé le plus proche possible des roues et dans le même axe.
- Lors de tests sur une carte `NUCLEO-F411RE`: la fonction `update()` de l'odométrie dure ~3 µs
- La classe `Odométrie` peut être modifiée pour ne plus contenir le `Ticker` qui lance automatiquement la fonction `update()`. Cette fonction peut ainsi être déclenchée dans le fichier `main.cpp` à l'aide d'un `Ticker`. Cela peut être utile pour effectuer à la suite l'**odométrie** puis l'**asservissement** dans une même fonction.