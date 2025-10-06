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
 - une pièce : elle ne peut renvoyer que deux valeurs, mais est dépendante d'un nombre de lancés donnés initialement (tips: utilisez une fonction récursive); au moindre lancé "pile", on arrête de lancer.
 - un deck de cartes : il est dépendant d'un nombre de couleurs et de valeurs, sa méthode de génération renvoie une valeur entre 1 et nombre couleurs * nombres valeurs, après deux tirages le premier sur la couleur, le second sur la valeur.

4/ Créez maintenant la méthode de tirage aléatoire pour chacun des éléments précédents et ainsi générer l'objet résultat (avec le bon statut).
Pour chaque type, calculez les statuts en fonction de la valeur retrouvée :
  - la plus petite : fumble
  - la valeur maximale : réussite critique
  - en dessous de la valeur médiane (score à 50%) : échec
  - au dessus de la médiane (score à 50%) : réussite

5/ Créez maintenant une classe GameMaster.
 - Un GameMaster dispose d'un nombre de dés conséquents de différents types, de deux decks de cartes l'un de trois couleurs de et 18 valeurs, le deuxième de 4 couleurs de 13 valeurs, et de deux pièces.
 - un GameMaster peut effectuer des tirages via la méthode `pleaseGiveMeACrit`. Le GameMaster sélectionne l'une des instances de Dice / Deck et Coin au hasard et renvoie une constante correspondant au type de résultat.

6/ Dans une vraie partie de JdR, les résulats ne sont pas fixes, ils sont souvent interprétés par le GameMaster en fonction d'un contexte. Modifiez votre classe de résultat afin qu'elle renvoie un score en pourcentage, puis déléguez la responsabilité de l'attribution du type de résultat (Critique / Succès / Echec / Fumble) à la classe GameMaster.

7/ Nous allons maintenant faire évoluer notre GameMaster pour qu'il soit capable de faire jouer des Scénarii à un ou plusieurs Aventuriers. Commençons par créer les classes suivantes :
 - **Encounter** : une rencontre contre un élément hostile, comporte un titre, une description et une échelle de score pour les 4 issues - c'est lui qui génèrera les objets Result désormais, vu qu'il peut comparer le score donné par le GameMaster à son échelle interne
 - **Scenario** : ensemble de rencontres avec un nom
 - **Adventurer** : représente un membre du groupe, il possède :
    - un nom
    - un niveau
    - un maximum de points de vie
    - un nombre de points de vie actuel

    et les méthodes pour le soigner, le blesser, le tuer et le faire monter de niveau.

8/ Design Pattern [Composite](https://refactoring.guru/fr/design-patterns/composite) - Pour simplifier l'implémentation des scenarii dans le cas où plusieurs aventuriers se rassemblent, il est possible d'abstraire le comportement d'un ensemble d'aventuriers comme un aventurier seul.
Créez donc la classe Party, qui hérite de Adventurer, et qui prend un vecteur d'Adventurer en paramètre. Adaptez ensuite les méthodes pour que les comportements s'adaptent à la situation de groupe :
  - Une blessure infligée l'est à l'aventurier qui a le plus de points de vies
  - Si un niveau doit être gagné, il l'est à celui qui a le niveau le plus bas
  - Le niveau du groupe est égal à la somme des niveaux des participants * 1+(2* nbAdventurer) - attention, il doit être immutable
  - Si on "tue" une Party, on tue un membre du groupe au hasard
