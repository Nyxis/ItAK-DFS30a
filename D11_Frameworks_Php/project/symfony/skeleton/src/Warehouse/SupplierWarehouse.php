<?php

namespace App\Warehouse;

use App\Entity\Variant;
use App\ValueObject\SellableStock;

class SupplierWarehouse implements WarehouseInterface
{
    public function supports(Variant $variant): bool
    {
        return true;
    }

    public function getSellableStock(Variant $variant): SellableStock
    {
        return new SellableStock(new \DateTime(), false, new \DateInterval('P7D'));
    }
}
