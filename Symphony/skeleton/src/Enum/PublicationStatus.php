<?php

namespace App\Enum;

enum PublicationStatus: string
{
case DRAFT = 'draft';
case PUBLISHED = 'published';
case ARCHIVED = 'archived';
}
