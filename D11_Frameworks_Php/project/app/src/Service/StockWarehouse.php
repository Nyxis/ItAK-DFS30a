<?php

namespace App\Service;

use App\Entity\VariantProduct;
use App\ValueObject\SellableStock;

class StockWarehouse implements WarehouseInterface
{
    private array $stock;

    public function __construct()
    {
        $this->stock = [];
    }

    public function addStock(VariantProduct $variant, int $quantity): void
    {
        $this->stock[$variant->getSku()] = $quantity;
    }

    public function supports(VariantProduct $variant): bool
    {
        return isset($this->stock[$variant->getSku()]);
    }

    public function getSellableStock(VariantProduct $variant): SellableStock
    {
        $quantity = $this->stock[$variant->getSku()] ?? 0;
        return new SellableStock(new \DateTimeImmutable(), $quantity);
    }
}
