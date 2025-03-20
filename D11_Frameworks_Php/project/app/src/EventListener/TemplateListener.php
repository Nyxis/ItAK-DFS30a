<?php

namespace App\EventListener;

use App\Attribute\Template;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpKernel\Event\ViewEvent;
use Symfony\Component\HttpKernel\Exception\NotFoundHttpException;
use Symfony\Component\HttpFoundation\Response;
use Twig\Environment;
use Twig\Error\Error;

class TemplateListener
{
    private Environment $twig;

    public function __construct(Environment $twig)
    {
        $this->twig = $twig;
    }

    public function __invoke(ViewEvent $event): void
    {
        $data = $event->getControllerResult();

        if (isset($data['redirect']) && $data['redirect'] instanceof RedirectResponse) {
            $event->setResponse($data['redirect']);
            return;
        }

        if (!is_array($data)) {
            $data = [];
        }

        $controllerCallable = $event->getRequest()->attributes->get('_controller');

        if (!$controllerCallable || !is_string($controllerCallable) || !str_contains($controllerCallable, '::')) {
            return;
        }

        [$controllerClass, $method] = explode('::', $controllerCallable);

        $reflection = new \ReflectionMethod($controllerClass, $method);
        $attributes = $reflection->getAttributes(Template::class);
        if (empty($attributes)) {
            return;
        }

        $templateAttribute = $attributes[0]->newInstance();
        $template = $templateAttribute->template;

        if (!$template) {
            throw new NotFoundHttpException('Le template n\'est pas défini dans l\'attribut #[Template]');
        }

        try {
            $responseContent = $this->twig->render($template, $data);
        } catch (Error $e) {
            throw new NotFoundHttpException("Le template '$template' est introuvable ou invalide.", $e);
        }

        $event->setResponse(new Response($responseContent));
    }
}