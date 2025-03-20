<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity]
class VariantProduct
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column(type: 'integer')]
    private ?int $id = null;

    #[ORM\Column(type: 'string', length: 50)]
    private string $sku;

    #[ORM\Column(type: 'integer')]
    private int $hdCapacity;

    #[ORM\Column(type: 'integer')]
    private int $screenSize;

    #[ORM\Column(type: 'string', length: 10)]
    private string $keyboardType;

    #[ORM\ManyToOne(targetEntity: Product::class, inversedBy: 'variants')]
    private Product $product;

    public function __construct(Product $product, int $hdCapacity, int $screenSize, string $keyboardType)
    {
        $this->product = $product;
        $this->hdCapacity = $hdCapacity;
        $this->screenSize = $screenSize;
        $this->keyboardType = $keyboardType;
        $this->sku = $this->generateSku();
    }

    private function generateSku(): string
    {
        return strtoupper(substr($this->product->getBrand(), 0, 3)) .
            '-' . $this->screenSize .
            '-' . ($this->keyboardType === 'AZERTY' ? 'AZ' : 'QW') .
            '-' . $this->hdCapacity;
    }

    public function setProduct(Product $param): void
    {
        $this->product = $param;
    }

    public function getSku(): string
    {
        return $this->sku;
    }
}
