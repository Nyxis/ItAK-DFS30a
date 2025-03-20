<?php

namespace App\ValueObject;

final readonly class SellableStock
{
    public function __construct(
        private \DateTimeInterface $now,
        private int|bool $quantity,
        private ?\DateInterval $availableIn = null
    ) {}

    public function isAvailable(): bool
    {
        return $this->quantity > 0;
    }

    public function getAvailability(): ?\DateTimeInterface
    {
        if ($this->isAvailable()) {
            return $this->now;
        }

        return $this->availableIn ? (clone $this->now)->add($this->availableIn) : null;
    }

    public function getQuantity(): int
    {
        return $this->quantity;
    }
}
