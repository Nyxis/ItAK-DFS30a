<?php

namespace App\Form;

use App\Entity\Product;
use App\Form\VariantProductType;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\Extension\Core\Type\CollectionType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;

class ProductType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->add('Product')
            ->add('brand')
            ->add('status')
            ->add('variants', CollectionType::class, [
                'entry_type'    => VariantProductType::class,
                'allow_add'     => true,
                'allow_delete'  => true,
                'by_reference'  => false,
            ]);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'data_class' => Product::class,
        ]);
    }
}
