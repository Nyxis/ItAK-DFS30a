FROM php:8.4-fpm

RUN apt-get update && apt-get install -y \
    libpq-dev \
    unzip \
    git \
    && docker-php-ext-install pdo pdo_mysql
RUN apt-get update && apt-get install -y sqlite3 libsqlite3-dev
RUN docker-php-ext-install pdo pdo_sqlite

RUN apt-get update && apt-get install -y wget \
    && wget https://get.symfony.com/cli/installer -O - | bash \
    && mv /root/.symfony5/bin/symfony /usr/local/bin/symfony


WORKDIR /var/www/symfony

COPY --from=composer:latest /usr/bin/composer /usr/bin/composer
