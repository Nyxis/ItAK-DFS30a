# Use PHP 8.4 with FPM
FROM php:8.4-fpm

# Install system dependencies
RUN apt-get update && apt-get install -y \
    libzip-dev \
    unzip \
    && docker-php-ext-install zip pdo_mysql

# Install Composer
COPY --from=composer:latest /usr/bin/composer /usr/bin/composer

# Set working directory
WORKDIR /var/www/html

# Create a new Symfony project if not exists
RUN if [ ! -f "composer.json" ]; then \
        composer create-project symfony/skeleton .; \
    fi

# Install dependencies
RUN composer install --no-dev --optimize-autoloader

CMD ["php-fpm"]
