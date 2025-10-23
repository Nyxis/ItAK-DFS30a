<?php

namespace App\Service;

use App\Entity\Variant;
use App\ValueObject\SellableStock;
use App\Warehouse\WarehouseInterface;

class WarehouseCollection
{
    /** @var WarehouseInterface[] */
    private iterable $warehouses;

    public function __construct(iterable $warehouses)
    {
        $this->warehouses = $warehouses;
    }

    public function getSellableStock(Variant $variant): SellableStock
    {
        foreach ($this->warehouses as $warehouse) {
            if ($warehouse->supports($variant)) {
                return $warehouse->getSellableStock($variant);
            }
        }

        return new SellableStock(new \DateTime(), false);
    }
}
