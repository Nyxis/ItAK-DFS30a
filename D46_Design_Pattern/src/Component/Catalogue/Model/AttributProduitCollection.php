<?php

namespace Component\Catalogue\Model;

class AttributProduitCollection
{
    public protected(set) array $attributProduits;

    public function __construct(
        AttributProduit ...$attributProduits
    ) {
        $this->attributProduits = $attributProduits;
    }
}
