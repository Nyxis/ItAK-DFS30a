<?php

namespace App\Entity;

use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity]
class Product
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column(type: 'integer')]
    private ?int $id = null;

    #[ORM\Column(type: 'string', length: 255)]
    private string $name;

    #[ORM\Column(type: 'string', length: 50)]
    private string $brand;

    #[ORM\Column(type: 'string', length: 20)]
    private string $status;

    #[ORM\OneToMany(mappedBy: 'product', targetEntity: VariantProduct::class, cascade: ['persist'], orphanRemoval: true)]
    private Collection $variants;

    public function __construct()
    {
        $this->variants = new ArrayCollection();
    }

    public function getVariants(): Collection
    {
        return $this->variants;
    }

    public function addVariant(VariantProduct $variant): void
    {
        if (!$this->variants->contains($variant)) {
            $this->variants[] = $variant;
            $variant->setProduct($this);
        }
    }

    public function removeVariant(VariantProduct $variant): void
    {
        if ($this->variants->contains($variant)) {
            $this->variants->removeElement($variant);
        }
    }

    public function getName(): string
    {
        return $this->name;
    }

    public function getStatus(): string
    {
        return $this->status;
    }

    public function getBrand(): string
    {
        return $this->brand;
    }

    public function setName(string $name): void
    {
        $this->name = $name;
    }

    public function setStatus(string $status): void
    {
        $this->status = $status;
    }

    public function setBrand(string $brand): void
    {
        $this->brand = $brand;
    }
}
