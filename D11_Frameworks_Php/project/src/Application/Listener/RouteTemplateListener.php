<?php

namespace Application\Listener;

use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\HttpKernel\Event\ViewEvent;
use Symfony\Component\HttpFoundation\Response;
use Twig\Environment as TemplatingEngine;
use Psr\Log\LoggerInterface;

class RouteTemplateListener implements EventSubscriberInterface
{
    /**
     * Fallback template format if undefined in routes
     */
    const FALLBACK_FORMAT = 'html';

    /**
     * @inherit_doc
     */
    public static function getSubscribedEvents()
    {
        return [
            KernelEvents::VIEW => 'onControllerView'
        ];
    }

    public function __construct(
        protected TemplatingEngine $templateEngine,
        protected LoggerInterface $logger
    ) {
    }

    public function onControllerView(ViewEvent $event)
    {
        $request = $event->getRequest();

        $template = $request->attributes->get(
            'template',
            $request->attributes->get('_route')
        );

        $format = $request->get('_format', self::FALLBACK_FORMAT);

        $templateChain = [
            $template,
            sprintf('%s.%s.twig', $template, $format),
        ];

        foreach ($templateChain as $templatePath) {
            if ($templatePath && $this->templateEngine->getLoader()->exists($templatePath)) {
                $event->setResponse(
                    new Response($this->templateEngine->render(
                        $templatePath,
                        $event->getControllerResult()
                    ))
                );

                return;
            }
        }

        $this->logger->info('No template guessed from routing while no Response returned from controller.', [
            'tried_templates' => $templateChain
        ]);
    }
}

