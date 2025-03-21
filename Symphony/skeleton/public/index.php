<?php

use App\Kernel;

require dirname(__DIR__) . '/vendor/autoload.php';

$context = array_merge([
    'APP_ENV' => $_SERVER['APP_ENV'] ?? 'dev',
    'APP_DEBUG' => (bool)($_SERVER['APP_DEBUG'] ?? true),
], $_SERVER);

$kernel = new Kernel($context['APP_ENV'], $context['APP_DEBUG']);
$response = $kernel->handle($request = \Symfony\Component\HttpFoundation\Request::createFromGlobals());

$response->send();

$kernel->terminate($request, $response);
