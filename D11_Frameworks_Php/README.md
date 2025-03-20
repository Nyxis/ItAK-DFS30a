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
```php
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

## Injection de dépendance - Design Patterns

Le composant d'injection de dépendance de Symfony permet d'implémenter facilement des Design Patterns difficiles à mettre en place dans d'autres contextes, comme par exemple le pattern Visitor.

Nous allons implémenter ce pattern, appliqué à une gestion de stocks multi-canal.
Pour connaitre la disponibilité d'un produit à la vente, nous devons interroger les entrepots sur un stock. Créez un service `WarehouseCollection`, qui expose une méthode `getSellableStock(VariantProduit $variant) : SellableStock`.

La classe SellableStock est un Value-Object, qui permet de définir un ensemble cohérent de données, reflettant une élément réel.
Voici son prototype :
```php
final readonly class SellableStock
{
    public function __construct(
        \DateTimeInterface $now,
        int|bool $quantity,
        ?\DateInterval $availableIn = null
    ){}

    public function isAvailable() : bool
    {}

    public function getAvailability() : \DateTimeInterface|null
    {}
}
```
Implémentez cette classe.

Créez maintenant deux classes qui implémentent un comportement d'entrepot, `WarehouseInterface` dont voici le prototype :
```php
interface WarehouseInterface
{
    public function supports(ProductVariant $variant) : bool;
    public function getSellableStock(ProductVariant $variant) : SellableStock;
}
```

L'une de ces Warehouses représente un fournisseur à qui nous pouvons passer des commandes, mais avec un délai; le second avec un stock prédéfini de VariantProduit, passés en construction.
Implémentez ces classes, puis utilisez la technique vu en cours pour les injecter sous forme d'iterable dans la `WarehouseCollection`.

Implémentez maintenant la méthode `getSellableStock` de WarehouseCollection pour qu'elle itère sur les WarehouseInterface, lise leur stock et produise un stock synthétique.

Si une nouvelle règle apparaît, comme par exemple un stock à l'étranger, seule l'implémentation d'une nouvelle WarehouseInterface ne sera nécessaire, sans modifier la structure des autres règles, ni les structure des données rendues.

## Sécurité

## Templating
