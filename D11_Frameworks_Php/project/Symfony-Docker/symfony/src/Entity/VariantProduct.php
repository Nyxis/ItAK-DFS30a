<?php

namespace App\Entity;

use App\Repository\VariantProductRepository;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity(repositoryClass: VariantProductRepository::class)]
class VariantProduct
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column]
    private ?int $id = null;

    #[ORM\Column]
    private ?int $hdCapacity = null;

    #[ORM\Column]
    private ?int $screncSize = null;

    #[ORM\Column(length: 255)]
    private ?string $keyBoardType = null;

    #[ORM\ManyToOne(targetEntity: Product::class, inversedBy: "variants")]
    #[ORM\JoinColumn(nullable: false)]
    private ?Product $product = null;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getHdCapacity(): ?int
    {
        return $this->hdCapacity;
    }

    public function setHdCapacity(int $hdCapacity): static
    {
        $this->hdCapacity = $hdCapacity;

        return $this;
    }

    public function getScrencSize(): ?int
    {
        return $this->screncSize;
    }

    public function setScrencSize(int $screncSize): static
    {
        $this->screncSize = $screncSize;

        return $this;
    }

    public function getKeyBoardType(): ?string
    {
        return $this->keyBoardType;
    }

    public function setKeyBoardType(string $keyBoardType): static
    {
        $this->keyBoardType = $keyBoardType;

        return $this;
    }
    
    public function getProduct(): ?Product
    {
        return $this->product;
    }

    public function setProduct(?Product $product): self
    {
        $this->product = $product;
        return $this;
    }
}
