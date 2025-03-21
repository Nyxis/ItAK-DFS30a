<?php

namespace App\Entity;

use App\Enum\Brand;
use App\Enum\PublicationStatus;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity]
class Product
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column]
    private ?int $id = null;

    #[ORM\Column(length: 255)]
    public string $name;

    #[ORM\Column(type: 'string', enumType: Brand::class)]
    public Brand $brand;

    #[ORM\Column(type: 'string', enumType: PublicationStatus::class)]
    public PublicationStatus $status;

    #[ORM\OneToMany(targetEntity: VariantProduit::class, mappedBy: 'product', cascade: ['persist', 'remove'], orphanRemoval: true)]
    private Collection $variants;

    public function __construct()
    {
        $this->variants = new ArrayCollection();
        $this->status = PublicationStatus::DRAFT;
        $this->brand = Brand::LENOVO;
        $this->name = '';
    }

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getName(): string
    {
        return $this->name;
    }

    public function setName(string $name): self
    {
        $this->name = $name;
        return $this;
    }

    public function getBrand(): Brand
    {
        return $this->brand;
    }

    public function setBrand(Brand $brand): self
    {
        $this->brand = $brand;
        return $this;
    }

    public function getStatus(): PublicationStatus
    {
        return $this->status;
    }

    public function setStatus(PublicationStatus $status): self
    {
        $this->status = $status;
        return $this;
    }

    public function getVariants(): Collection
    {
        return $this->variants;
    }

    public function addVariant(VariantProduit $variant): self
    {
        if (!$this->variants->contains($variant)) {
            $this->variants[] = $variant;
        }
        return $this;
    }

    public function removeVariant(VariantProduit $variant): self
    {
        $this->variants->removeElement($variant);
        return $this;
    }
}