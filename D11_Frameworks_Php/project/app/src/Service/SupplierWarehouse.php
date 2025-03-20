<?php

namespace App\Service;

use App\Entity\VariantProduct;
use App\ValueObject\SellableStock;

class SupplierWarehouse implements WarehouseInterface
{

    private array $leadTime = [];

    public function addSupplierData(VariantProduct $variant, string $interval): void
    {
        $this->leadTime[$variant->getSku()] = $interval;
    }

    public function supports(VariantProduct $variant): bool
    {
        return true;
    }

    public function getSellableStock(VariantProduct $variant): SellableStock
    {
        $interval = $this->leadTime[$variant->getSku()] ?? 'P14D';
        return new SellableStock(new \DateTimeImmutable(), 0, new \DateInterval($interval));
    }
}
