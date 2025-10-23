<?php
namespace App\EventListener;

use Symfony\Component\HttpKernel\Event\ViewEvent;
use Symfony\Component\HttpFoundation\Response;
use Twig\Environment;

class TemplateListener
{
    private $twig;

    public function __construct(Environment $twig)
    {
        $this->twig = $twig;
    }

    public function onKernelView(ViewEvent $event)
    {
        $request = $event->getRequest();
        $template = $request->attributes->get('template');

        if ($template && $this->twig->getLoader()->exists($template)) {
            $controllerResult = $event->getControllerResult();

            if (!$controllerResult instanceof Response) {
                $response = new Response($this->twig->render($template, $controllerResult));
                $event->setResponse($response);
            }
        }
    }
}