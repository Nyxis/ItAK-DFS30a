FROM php:8.4-fpm

# Installez les extensions PHP nécessaires
RUN apt-get update && apt-get install -y \
    libzip-dev \
    unzip \
    && docker-php-ext-install zip pdo_mysql

# Installez Composer
COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

# Définissez le répertoire de travail
WORKDIR /var/www/html

# Donnez les permissions appropriées
RUN chown -R www-data:www-data /var/www/html \
    && chmod -R 755 /var/www/html