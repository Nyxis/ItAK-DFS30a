<?php

namespace App\Controller;

use App\Attribute\Template;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;

class HomeController extends AbstractController
{
    #[Route("/", name: "home")]
    #[Template("home.html.twig")]
    public function index(): array
    {
        return [
            'title' => 'Enfiiiiiiiin !'
        ];
    }
}
