<?php

namespace App\EventSubscriber;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\ViewEvent;
use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\HttpFoundation\Response;
use Twig\Environment;

class TemplateSubscriber implements EventSubscriberInterface
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

    public static function getSubscribedEvents()
    {
        return [
            KernelEvents::VIEW => 'onKernelView',
        ];
    }
}