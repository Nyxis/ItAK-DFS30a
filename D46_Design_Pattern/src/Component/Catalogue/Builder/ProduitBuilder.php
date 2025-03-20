<?php 
    namespace Component\Catalogue\Builder;

use Component\Catalogue\Model\Produit;

class ProduitBuilder
{
    private array $data = [];
    private array $filters = [];
    private Produit $prototype;

    public function from(string $filePath): self
    {
        $data = file_get_contents($filePath);
        $this->data = json_decode($data, true);
        return $this;
    }

    public function addFilter(callable $filter): self
    {
        $this->filters[] = $filter;
        return $this;
    }

    public function setPrototype(Produit $prototype): self
    {
        $this->prototype = $prototype;
        return $this;
    }

    public function build(): array
    {
        $result = $this->data;

        // Appliquer les filtres
        foreach ($this->filters as $filter) {
            $result = array_filter($result, $filter);
        }

        // Construire les produits
        $produits = [];
        foreach ($result as $item) {
            $produitClone = clone $this->prototype;
            $produitClone->ean = $item['ean'];
            $produitClone->type = $item['type'];
            $produitClone->designation = $item['designation'] ?? null;
            $produitClone->poids = $item['poids'] ?? null;
            $produitClone->mission = $item['mission'] ?? null;
            $produitClone->duree = $item['duree'] ?? null;

            $produits[] = $produitClone;
        }

        return $produits;
    }
}

?>