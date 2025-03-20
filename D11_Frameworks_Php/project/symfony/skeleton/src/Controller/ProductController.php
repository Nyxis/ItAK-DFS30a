<?php

namespace App\Controller;

use App\Entity\Product;
use App\Form\ProductType;
use Doctrine\ORM\EntityManagerInterface;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;
use App\Entity\Variant;
use App\Service\WarehouseCollection;
use App\Repository\VariantRepository;
use Symfony\Component\HttpKernel\Exception\NotFoundHttpException;

class ProductController extends AbstractController
{
    public function show(): array
    {
        return [
            'controller_name' => 'ProductController',
        ];
    }

    
    #[Route("/product/new", name: "product_new")]
    public function new(Request $request, EntityManagerInterface $entityManager): Response
    {
        $product = new Product();
        $form = $this->createForm(ProductType::class, $product);

        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            foreach ($product->getVariants() as $variant) {
                $variant->setProduct($product);
                $entityManager->persist($variant);
            }
        
            $entityManager->persist($product);
            $entityManager->flush();
        
            return $this->redirectToRoute('product_success');
        }

        return $this->render('product/new.html.twig', [
            'form' => $form->createView(),
        ]);
    }
        
     #[Route("/product/success", name: "product_success")]
    public function success(EntityManagerInterface $entityManager): Response
    {
        $product = $entityManager->getRepository(Product::class)->findOneBy([], ['id' => 'DESC']); // Dernier produit créé

        if (!$product) {
            throw $this->createNotFoundException('No product found');
        }

        return $this->render('product/success.html.twig', [
            'product' => $product,
        ]); 
    }

    #[Route('/variant/{id}/stock', name: 'variant_stock')]
    public function getStock(int $id, VariantRepository $variantRepository, WarehouseCollection $warehouseCollection): Response
    {
        $variants = $variantRepository->findBy(['product' => $id]);

        if (!$variants) {
            throw new NotFoundHttpException("Variant not found");
        }

        $productName = $variants[0]->getProduct()->getName();

        $sellableStocks = [];

        foreach ($variants as $variant) {
            $sellableStock = $warehouseCollection->getSellableStock($variant);

            $sellableStocks[] = [
                'productName' => $productName,
                'variant' => $variant,
                'sellableStock' => $sellableStock,
            ];
        }
        return $this->render('product/stock.html.twig', [
            'productName' => $productName,
            'variants' => $variants,
            'sellableStocks' => $sellableStocks,
        ]);
    }
}
