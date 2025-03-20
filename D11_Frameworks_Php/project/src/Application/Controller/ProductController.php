<?php

namespace Application\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;

/**
 * Controller class for all Product use cases
 */
class ProductController extends AbstractController
{
    public function listAction()
    {
        return ['foo' => 'barz'];
    }

    protected function formAction()
    {

    }

    public function createAction()
    {

    }

    public function updateAction()
    {

    }
}
