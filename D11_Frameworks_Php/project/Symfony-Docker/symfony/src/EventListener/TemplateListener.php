<?php

namespace App\EventListener;

use App\Attribute\Template;
use Symfony\Component\HttpKernel\Event\ViewEvent;
use Symfony\Component\HttpKernel\Exception\NotFoundHttpException;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\RedirectResponse;
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
        // On récupère les données retournées par le contrôleur
        $data = $event->getControllerResult();

        if (isset($data['redirect']) && $data['redirect'] instanceof RedirectResponse) {
            $event->setResponse($data['redirect']);
            return;
        }

        if (!is_array($data)) {
            $data = [];
        }

        // On récupère le contrôleur et la méthode exécutée
        $controllerCallable = $event->getRequest()->attributes->get('_controller');

        // On vérifie si le contrôleur est une string et contient '::'
        if (!is_string($controllerCallable) || !str_contains($controllerCallable, '::')) {
            return;
        }

        // On récupère le nom de la classe et de la méthode
        [$controllerClass, $method] = explode('::', $controllerCallable);

        // On vérifie si la méthode a un attribut #[Template]
        $reflection = new \ReflectionMethod($controllerClass, $method);
        $attributes = $reflection->getAttributes(Template::class);
        if (empty($attributes)) {
            return;
        }

        // On récupère la template depuis l'attribut
        $templateAttribute = $attributes[0]->newInstance();
        $template = $templateAttribute->template;

        if (!$template) {
            throw new NotFoundHttpException('Le template n\'est pas défini dans l\'attribut #[Template]');
        }

        // On vérifie si la template existe et on le rend
        try {
            $responseContent = $this->twig->render($template, $data);
        } catch (Error $e) {
            throw new NotFoundHttpException("Le template '$template' est introuvable ou invalide.", $e);
        }

        // On remplace la réponse de l'événement
        $event->setResponse(new Response($responseContent));
    }
}
