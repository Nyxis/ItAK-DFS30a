<?php

namespace App\Service;

use App\Entity\VariantProduct;
use App\ValueObject\SellableStock;

interface WarehouseInterface
{
    public function supports(VariantProduct $variant): bool;
    public function getSellableStock(VariantProduct $variant): SellableStock;
}
