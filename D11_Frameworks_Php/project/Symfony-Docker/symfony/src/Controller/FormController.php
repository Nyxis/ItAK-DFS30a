<?php

namespace App\Controller;

use App\Attribute\Template;
use App\Entity\Product;
use App\Form\ProductType;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;
use Doctrine\ORM\EntityManagerInterface;

class FormController extends AbstractController
{
    #[Template("product_form.html.twig")]
    public function index(Request $request, EntityManagerInterface $em): array
    {
        $product = new Product();
        $form = $this->createForm(ProductType::class, $product);
        $form->handleRequest($request);

        if ($form->isSubmitted() && $form->isValid()) {
            $em->persist($product);
            $em->flush();
        }

        return [
            'form' => $form->createView(),
        ];  
    }
}
