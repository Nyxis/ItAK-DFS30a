<?php

namespace App\Attribute;

use Attribute;

#[Attribute(Attribute::TARGET_METHOD)]
class Template
{
    public function __construct(public string $template)
    {
    }
}
