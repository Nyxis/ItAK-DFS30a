<?php
namespace App\Entity;

use App\Enum\KeyBoardType;
use Doctrine\ORM\Mapping as ORM;

#[ORM\Entity]
readonly class VariantProduit
{
    #[ORM\Id]
    #[ORM\GeneratedValue]
    #[ORM\Column]
    private ?int $id;

    public function __construct(
        #[ORM\Column(length: 50)]
        public string $sku,
        #[ORM\Column]
        public int $hdCapacity,
        #[ORM\Column]
        public int $screenSize,
        #[ORM\Column(type: 'string', enumType: KeyBoardType::class)]
        public KeyBoardType $keyboardType,
        #[ORM\ManyToOne(targetEntity: Product::class, inversedBy: 'variants')]
        public ?Product $product = null
    ) {

    }
    public function getId(): ?int
    {
        return $this->id;
    }
}