<?php

namespace Component\Catalogue\Model;

class AttributProduitCollection
{
    protected array $attributProduits;

    public function __construct(
        AttributProduit ...$attributProduits
    ) {
        $this->attributProduits = $attributProduits;
    }
    
    public function __set ($attributProduits, $value) {
        $this->attributProduits = $value;
    }
    
}
