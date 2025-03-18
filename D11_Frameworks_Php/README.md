# D11 - Frameworks Php

Le but de l'exercice est d'appliquer les concepts vus en cours à travers les exercices d'application ci-dessous.

## Installation

En utilisant 3 containers Docker, créer un environnement de travail avec un reverse proxy (Apache ou Nginx), une base de donnée (MariahDB ou MySQL) et un Php-fpm (8.4).

Le reverse proxy doit appeler le container Php à chaque requête reçue.

Via le container Php, créer un nouveau projet Symfony, avec sa version minimale. Ajoutez les composants nécessaires à utilisation simple, en contexte web (ORM, Twig, Security, Form...).

Vous installerez votre projet dans le dossier ```projet```.

## Fichiers de routes

Les attributs et annotations proposées par Symfony ne respectent pas le principe de Single Responsability. Aussi, leur utilisation obfusquent certaines options bien pratiques pour gagner du temps en utilisant le framework.

Pour commencer, créez un fichier de routes spécifique à une zone fonctionnelle dans le projet, par exemple ```config/routes/product.yaml```; puis référencez le dans votre fichier de routes principal (https://symfony.com/doc/current/routing.html#route-groups-and-prefixes).

Créez ensuite quelques routes. Dans chacune, créez un attribut ```template```, dans lequel vous référencez le template souhaité pour cette route.

Ensuite, utilisez les mécaniques vues en cours pour intercepter toutes les requêtes de l'application, une fois leur retour renvoyé par leur controller respectif.
Implémentez la mécanique suivante :
 - Si la route de la requête dispose de l'attribut template, que ce template existe et si le controller n'a pas renvoyé de ResponseInterface
 - Alors créez et retournez une Response en appelant le template référencé par la route, avec le retour du controller en paramètre

## Formulaires

Nous allons créer un back-office simple pour gérer un catalogue d'ordinateurs, variants sur la capacité de disque dûr, taille de l'écran et type de clavier (qwerty / azerty). Nous souhaitons également gérer le nom du produit, leur marque (Apple / Lenovo / MSI) et leur statut de publication (draft / published / archived).

Créez une page qui affiche un formulaire permettant d'entrer les informations produit en utilisant le composant Formulaire de Symfony pour le prototypage, l'affichage et le mapping des informations avec votre modèle.

Ajoutez à votre formulaire un nouveau champ pour gérer les variants de votre produit. Vous devrez pouvoir gérer l'ajout et le retrait d'un variant.

Implémentez les règles suivantes en utilisant le composant formulaire uniquement :
 - Apple ne propose que des tailles d'écran 14 et 16 pouces, alors que les autres 15 et 17 pouces.
 - MSI ne vend pas de disque dûr de moins de 2 To.

Ajoutez un attribut SKU aux variants produit.
Ce SKU doit être autogénéré à partir des 3 premières lettres de la marque en majuscule - taille écran - AZ|QW - taille disque. Exemple : APP-16-AZ-2000. La génération doit se faire via le composant formulaire, et il doit être initialisé dès la construction du variant en respectant le prototype suivant :
```html+php
readonly class VariantProduit
{
    public function __construct(
        public string $sku,
        public int $hdCapacity,
        public int $screenSize,
        public KeyBoardType $keyboardType
    ){
    }
}
```

## Sécurité

