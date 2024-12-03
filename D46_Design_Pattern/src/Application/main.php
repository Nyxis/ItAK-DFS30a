<?php

// register Autoloader
define('PROJECT_DIR', realpath(__DIR__.'/..'));
require_once PROJECT_DIR.'/Lib/Autoloader.php';

new Autoloader(PROJECT_DIR);

use Component\Catalogue\Model;

/**
 * Main function
 */
function main(array $args) {

    $produit = new Model\Produit(
        '1000011333404012220',
        Model\TypeProduit::MARCHANDISE,
        new Model\AttributProduitCollection(
            new Model\AttributProduit('code_barre', 123456),
            new Model\AttributProduit('designation', 'Chtulhu Rlyeh FTARGN')
        )
    );

    var_dump($produit);
}

return main($argv);
