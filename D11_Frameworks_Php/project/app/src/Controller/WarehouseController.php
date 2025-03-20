<?php

namespace App\Controller;

use App\Entity\VariantProduct;
use App\Service\WarehouseCollection;
use Doctrine\ORM\EntityManagerInterface;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

class WarehouseController extends AbstractController
{
    #[Route('/stock/{sku}', name: 'check_stock')]
    public function checkStock(WarehouseCollection $warehouseCollection, string $sku, EntityManagerInterface $em): Response
    {
        // 🔍 On cherche le VariantProduct en base avec le SKU
        $variant = $em->getRepository(VariantProduct::class)->findOneBy(['sku' => $sku]);

        if (!$variant) {
            return new Response("Aucune variante trouvée avec ce SKU.", Response::HTTP_NOT_FOUND);
        }

        $stock = $warehouseCollection->getSellableStock($variant);

        if ($stock->isAvailable()) {
            return new Response("Stock: Disponible immédiatement ✅ (Quantité: {$stock->getQuantity()})");
        }

        if ($stock->getAvailability()) {
            $days = $stock->getAvailability()->diff(new \DateTimeImmutable())->days;
            return new Response("Stock disponible sous {$days} jours ⏳");
        }

        return new Response("Stock: Non disponible ❌");

    }
}
