<?php

class Autoloader
{
    public function __construct(
        private ?string $projectDir = null
    ) {
        $this->projectDir = $this->projectDir ?: realpath(__DIR__);

        spl_autoload_register(function ($classname) {

            $globPattern = sprintf('%s%s%s.php',
                $this->projectDir,
                DIRECTORY_SEPARATOR,
                str_replace('\\', DIRECTORY_SEPARATOR, $classname)
            );

            foreach (glob($globPattern) as $phpFile) {
                require_once($phpFile);
            }
        });
    }
}
