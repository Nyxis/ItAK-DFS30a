Formulaire d'ajout de produit incomplet.  
J'ai fait le plus gros je pense du Pattern Visitor mais je n'arrivais pas à lire des stocks disponibles. Et c'est tout ce que j'ai eu le temps de faire.  
Initialisation du projet classique, `docker compose build` => `docker compose up` => `docker exec -it symfony_php bash` => `composer install` => `php bin/console d:m:m`  
Ensuite j'ai créé une route **/generate-products** pour créer des produits et variantes.  
La route **/stock/{sku}** parmi celles généré, par exemple **/stock/APP-16-AZ-4000** pour un message de la disponibilité des stocks.