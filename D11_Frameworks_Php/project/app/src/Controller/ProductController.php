<?php

namespace App\Controller;

use App\Entity\Product;
use App\Entity\VariantProduct;
use App\Form\ProductFormType;
use App\Service\StockWarehouse;
use App\Service\SupplierWarehouse;
use Doctrine\ORM\EntityManagerInterface;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use App\Attribute\Template;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

class ProductController extends AbstractController
{
    #[Template('product/index.html.twig')]
    public function index(): array
    {
        return [
            'title' => 'Liste des produits',
            'products' => [
                ['id' => 1, 'name' => 'Produit A', 'price' => 10],
                ['id' => 2, 'name' => 'Produit B', 'price' => 20],
            ]
        ];
    }

    #[Template('product/new.html.twig')]
    public function new(Request $request, EntityManagerInterface $em): array
    {
        $product = new Product();
        $form = $this->createForm(ProductFormType::class, $product);

        $form->handleRequest($request);
        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($product);
            $em->flush();

            return [
                'redirect' => $this->redirectToRoute('product_index')
            ];
        }

        return [
            'form' => $form->createView(),
        ];
    }

    #[Template('product/show.html.twig')]
    public function show(int $id): array
    {
        return [
            'id' => $id,
            'name' => 'Produit ' . chr(65 + $id), // Génère A, B, C...
            'price' => $id * 10
        ];
    }

    #[Route('/generate-products', name: 'generate_products')]
    public function generateProducts(EntityManagerInterface $em, StockWarehouse $stockWarehouse, SupplierWarehouse $supplierWarehouse): Response
    {
        $brands = ['Apple', 'Lenovo', 'MSI'];
        $statuses = ['draft', 'published', 'archived'];

        foreach ($brands as $brand) {
            $product = new Product();
            $product->setName($brand . " Laptop");
            $product->setBrand($brand);
            $product->setStatus($statuses[array_rand($statuses)]);

            $em->persist($product);

            $variantsData = [
                [1000, 14, 'AZERTY'],
                [2000, 15, 'QWERTY'],
                [4000, 16, 'AZERTY'],
            ];

            foreach ($variantsData as [$hdCapacity, $screenSize, $keyboardType]) {
                $variant = new VariantProduct($product, $hdCapacity, $screenSize, $keyboardType);
                $em->persist($variant);

                $quantity = random_int(0, 10);
                $stockWarehouse->addStock($variant, $quantity);

                $delayDays = random_int(5, 14); // Délai entre 5 et 14 jours
                $supplierWarehouse->addSupplierData($variant, 'P' . $delayDays . 'D');
            }
        }

        $em->flush();

        return new Response("Produits et variantes générés avec succès ! ✅");
    }
}
