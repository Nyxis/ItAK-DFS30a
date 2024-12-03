<?php

namespace Component\Catalogue\Model;

class AttributProduit
{
    public function __construct(
        protected string $code,
        protected $value
    ) {
    }
}
