<?php

namespace Component\Catalogue\Model;

class Produit
{
    public function __construct(
        public string $ean,
        public string $type,
        public ?string $designation = null,
        public ?int $poids = null,
        public ?string $mission = null,
        public ?int $duree = null
    ) {
    }

   
}

