<?php

namespace App\Warehouse;

use App\Entity\Variant;
use App\ValueObject\SellableStock;

interface WarehouseInterface
{
    public function supports(Variant $variant): bool;
    public function getSellableStock(Variant $variant): SellableStock;
}