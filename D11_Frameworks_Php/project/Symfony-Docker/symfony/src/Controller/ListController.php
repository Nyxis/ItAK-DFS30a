<?php

namespace App\Controller;

use App\Attribute\Template;
use App\Repository\ProductRepository;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;

class ListController extends AbstractController
{
    #[Template("product_list.html.twig")]
    public function index(ProductRepository $productRepository): Array
    {
        $products = $productRepository->findAll();

        return [
            'products' => $products,
        ];
    }
}