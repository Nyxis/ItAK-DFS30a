# D46 - Design Pattern

Dans ces exercices, nous appliquerons les principes SOLID vus en cours pour se démarquer du modèle "Database Driven Developpement" et s'orienter vers la logique "Code first" et la "Clean Architecture".

Nous améliorerons notre code au fur et à mesure des exercices, en implémantant des Design Pattern pour aider à résoudre des problèmes plus complexes, sans complexifier le code, sa sécurité et sa maintenance.

*Tips* : Pour exécuter le programme, vous pouvez utiliser Docker pour travailler sur la dernière version de Php sans avoir à l'installer directement dans votre environnement :
```sh
docker run --rm -v "$(pwd)/D46_Design_Pattern":/app -w /app php:8.4-cli-alpine php src/Application/main.php
```

*Ressources utiles* :
 - Explication et schéma des design patterns usuels : https://refactoring.guru/design-patterns

## Créer un modèle de classes

Notre client souhaite pouvoir visualiser une liste de produits et de fournisseurs, chaque produit pouvant être acheté à des fournisseurs différents à des prix différents.
Nous devons également pouvoir générer des commandes de certains produits à un fournisseur précis.
Chaque réception de commande devra alimenter le stock.
Le donneur d'ordre des opérations doit pouvoir être identifié, de même que son bénéficiaire.
Les produits peuvent également être de plusieurs types, marchandise et service dans un premier temps.

Créez une structure de classes pour matérialiser ce modèle. Pensez à découper ce modèle en différents modules afin de visualiser les dépendances fonctionnelles dans votre code (il ne doit pas être possible de faire des cercles de dépendances : A dépend de B qui dépend de C qui dépend de A).

Vous livrerez une instanciation complète de chacune des classes du modèle dans le fichier `main.php`.

## Builder / Prototype

Le pattern Prototype permet de créer des objets à partir d'une définition dynamique (les attributs peuvent être variables sans avoir à créer de nouvelles classes).

Le pattern Builder permet de modifier le cycle de création d'un objet de manière dynamique (comme par exemple ajouter des filtres de recherche).

Nous allons appliquer ces deux patterns pour créer nos objets `Produit` à partir d'une source de données externe, et ensuite de permettre de lui donner une structure différente en fonction de son `TypeProduit`.

Code cible :
```php
// main.php

$.... = (new ....Builder())
    ->from('data/products.json')
    ->addfilter(fn(array $data) => $data['....'] == '.....')
    ->setPrototype(...Prototype)
    ->build()
;

foreach ($..... as $produit) {
    var_dump($produit);
}

```

Vous respecterez les principes SOLID.

## Adapter

## State Machine


