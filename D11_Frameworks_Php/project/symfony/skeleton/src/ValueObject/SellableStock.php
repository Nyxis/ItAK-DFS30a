<?php

namespace App\ValueObject;

final class SellableStock
{
    public function __construct(
        private readonly \DateTimeInterface $now,
        private readonly int|bool $quantity,
        private readonly ?\DateInterval $availableIn = null
    ) {}

    public function isAvailable(): bool
    {
        return $this->quantity !== false && $this->quantity > 0;
    }

    public function getAvailability(): ?\DateTimeInterface
    {
        return $this->availableIn ? (clone $this->now)->add($this->availableIn) : null;
    }

    public function getQuantity(): int|bool
    {
        return $this->quantity;
    }
}
