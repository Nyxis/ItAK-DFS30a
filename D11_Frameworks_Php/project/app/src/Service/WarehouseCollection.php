<?php

namespace App\Service;

use App\Entity\VariantProduct;
use App\ValueObject\SellableStock;

class WarehouseCollection
{
    /** @var WarehouseInterface[] */
    private iterable $warehouses;

    public function __construct(iterable $warehouses)
    {
        $this->warehouses = $warehouses;
    }

    public function getSellableStock(VariantProduct $variant): SellableStock
    {
        foreach ($this->warehouses as $warehouse) {
            if ($warehouse->supports($variant)) {
                return $warehouse->getSellableStock($variant);
            }
        }

        return new SellableStock(new \DateTimeImmutable(), 0);
    }
}
