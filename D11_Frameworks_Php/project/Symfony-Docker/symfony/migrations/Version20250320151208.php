<?php

declare(strict_types=1);

namespace DoctrineMigrations;

use Doctrine\DBAL\Schema\Schema;
use Doctrine\Migrations\AbstractMigration;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
final class Version20250320151208 extends AbstractMigration
{
    public function getDescription(): string
    {
        return '';
    }

    public function up(Schema $schema): void
    {
        // this up() migration is auto-generated, please modify it to your needs
        $this->addSql('CREATE TEMPORARY TABLE __temp__variant_product AS SELECT id, product_id, hd_capacity, screnc_size, key_board_type FROM variant_product');
        $this->addSql('DROP TABLE variant_product');
        $this->addSql('CREATE TABLE variant_product (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, product_id INTEGER DEFAULT NULL, product1_id INTEGER DEFAULT NULL, hd_capacity INTEGER NOT NULL, screnc_size INTEGER NOT NULL, key_board_type VARCHAR(255) NOT NULL, CONSTRAINT FK_BCEF29EB4584665A FOREIGN KEY (product_id) REFERENCES product (id) ON UPDATE NO ACTION ON DELETE NO ACTION NOT DEFERRABLE INITIALLY IMMEDIATE, CONSTRAINT FK_BCEF29EB5D97111F FOREIGN KEY (product1_id) REFERENCES product (id) NOT DEFERRABLE INITIALLY IMMEDIATE)');
        $this->addSql('INSERT INTO variant_product (id, product_id, hd_capacity, screnc_size, key_board_type) SELECT id, product_id, hd_capacity, screnc_size, key_board_type FROM __temp__variant_product');
        $this->addSql('DROP TABLE __temp__variant_product');
        $this->addSql('CREATE INDEX IDX_BCEF29EB4584665A ON variant_product (product_id)');
        $this->addSql('CREATE INDEX IDX_BCEF29EB5D97111F ON variant_product (product1_id)');
    }

    public function down(Schema $schema): void
    {
        // this down() migration is auto-generated, please modify it to your needs
        $this->addSql('CREATE TEMPORARY TABLE __temp__variant_product AS SELECT id, product_id, hd_capacity, screnc_size, key_board_type FROM variant_product');
        $this->addSql('DROP TABLE variant_product');
        $this->addSql('CREATE TABLE variant_product (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, product_id INTEGER DEFAULT NULL, hd_capacity INTEGER NOT NULL, screnc_size INTEGER NOT NULL, key_board_type VARCHAR(255) NOT NULL, CONSTRAINT FK_BCEF29EB4584665A FOREIGN KEY (product_id) REFERENCES product (id) NOT DEFERRABLE INITIALLY IMMEDIATE)');
        $this->addSql('INSERT INTO variant_product (id, product_id, hd_capacity, screnc_size, key_board_type) SELECT id, product_id, hd_capacity, screnc_size, key_board_type FROM __temp__variant_product');
        $this->addSql('DROP TABLE __temp__variant_product');
        $this->addSql('CREATE INDEX IDX_BCEF29EB4584665A ON variant_product (product_id)');
    }
}
