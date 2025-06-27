<?php

namespace App\Warehouse;

use App\Entity\Variant;
use App\ValueObject\SellableStock;

class LocalWarehouse implements WarehouseInterface
{
    public function supports(Variant $variant): bool
    {
        return true;
    }

    public function getSellableStock(Variant $variant): SellableStock
    {
        return new SellableStock(new \DateTime(), rand(0, 10));
    }
}
