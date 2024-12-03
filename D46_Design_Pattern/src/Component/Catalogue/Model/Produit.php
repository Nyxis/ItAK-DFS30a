<?php

namespace Component\Catalogue\Model;

class Produit
{
    public function __construct(
        protected string $ean,
        protected TypeProduit $typeProduit,
        protected AttributProduitCollection $attributProduits
    ) {
    }
}
