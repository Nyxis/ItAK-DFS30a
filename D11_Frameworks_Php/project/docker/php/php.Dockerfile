FROM php:8.4-fpm

# Installer les extensions PHP nécessaires
RUN apt-get update && apt-get install -y \
    unzip git curl libpq-dev libzip-dev \
    && docker-php-ext-install pdo pdo_mysql zip

# Installer Composer
COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

# Définir le répertoire de travail
WORKDIR /var/www/html
