# Programmation Orientée Objet : C++

## Installation et Makefile

Pour produire un code clair et structuré, adoptons une structure de fichiers propres :
```
\ mon_projet
  |  \ build         # contient les fichiers compilées (binaires)
  |  \ includes      # contient les headers
  |  \ src           # contient les fichiers source (les implémentations)
  |
  | .gitignore       # fichiers ignorés par git (les fichiers compilés)
  | Makefile         # contient les instructions de compilation du projet
  |
```

Créez votre fichier `src/main.cpp` qui écrit "hello world" sur la sortie standard.
Compilez avec le Makefile fourni via `make`.
Lancez ensuite votre programme avec `./build/app`.

*Tip* : `make; ./build/app; make clean`

## Programmation orientée objet

Dans le but d'animer une soirée de JdR, un Game Master emmène un ensemble de matériel pour gérer les tirages aléatoires conséquents aux choix des joueurs.

À chaque action, le Game Master choisira au hasard l'un des éléments en sa possession pour tirer la valeur.
Cette valeur pourra être une réussite, un échec, une réussite critique ou un fumble. Selon l'action, le taux de réussite, de critique et de fumble sera variable, il faudra donc générer un score de réussite en pourcentage pour chaque éléments et le comparer à l'échelle prédéfinie.

1/ Modéliser une classe qui représente un résultat de tirage aléatoire.

2/ Modéliser une classe qui représente le comportement du tirage de ces valeurs aléatoires.

3/ Le GM a à sa disposition 3 types de matériels. Créez et implémentez les classes correspondantes en C++, en utilisant le comportement créé précédemment.
 - le dé : il peut être créé avec un nombre de faces. Il génère une valeur correspondante à l'une de ses faces lors du tirage
 - une pièce : elle ne peut renvoyer que deux valeurs, mais est dépendante d'un nombre de lancés donnés initialement (tips: utilisez une fonction récursive)
 - un deck de cartes : il est dépendant d'un nombre de couleurs et de valeurs, sa méthode de génération renvoie une valeur entre 1 et nombre couleurs * nombres valeurs, après deux tirages le premier sur la couleur, le second sur la valeur.

4/ Créez maintenant la méthode de tirage aléatoire pour chacun des éléments précédents et ainsi générer l'objet résultat (avec le bon statut).
Pour chaque type, calculez les statut en fonction de la valeur retrouvée :
    - la plus petite : fumble
    - la valeur maximale : réussite critique
    - en dessous de la valeur médiane : échec
    - au dessus de la médiane : réussite

5/ Créez maintenant une classe GameMaster.
 - Un GameMaster dispose d'un nombre de dés conséquents de différents types, de deux decks de cartes l'un de trois couleurs de et 18 valeurs, le deuxième de 4 couleurs de 13 valeurs, et de deux pièces.
 - un GameMaster peut effectuer des tirages via la méthode `pleaseGiveMeACrit`. Le GameMaster sélectionne l'une des instances de Dice / Deck et Coin au hasard et renvoie une constante correspondant au type de résultat.

6/ Dans une vraie partie de JdR, les résulats ne sont pas fixes, ils sont souvent interprétés par le GameMaster en fonction d'un contexte. Modifiez votre classe de résultat afin qu'elle renvoie un score en pourcentage, puis déléguez la responsabilité de l'attribution du type de résultat (Critique / Succès / Echec / Fumble) à la classe GameMaster.
