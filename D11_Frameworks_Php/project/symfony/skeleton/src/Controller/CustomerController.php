<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Attribute\Route;

class CustomerController extends AbstractController
{
    public function show(): array
    {
        return [
            'controller_name' => 'CustomerController',
        ];
    }
}
