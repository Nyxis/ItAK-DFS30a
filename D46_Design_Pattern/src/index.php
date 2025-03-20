<?php
require_once __DIR__ . '/vendor/autoload.php';

use Component\Catalogue\Builder\ProduitBuilder;
use Component\Catalogue\Model\Produit;
use Component\Catalogue\Model\TypeProduit;

// Prototype de produit de base
$prototype = new Produit(
    ean: '',
    type: TypeProduit::MARCHANDISE
);

// Création des produits via Builder
$produits = (new ProduitBuilder())
    ->from(__DIR__ . '/../../data/products.json')
    ->addFilter(fn($data) => $data['type'] === TypeProduit::MARCHANDISE)
    ->setPrototype($prototype)
    ->build();

// Affichage des produits
foreach ($produits as $produit) {
    var_dump($produit);
}
