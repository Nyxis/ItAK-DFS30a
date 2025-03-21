<?php

namespace App\Form;

use App\Entity\Product;
use App\Enum\Brand;
use App\Enum\PublicationStatus;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\Extension\Core\Type\ChoiceType;
use Symfony\Component\Form\Extension\Core\Type\CollectionType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;

class ProductType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->add('name')
            ->add('brand', ChoiceType::class, [
                'choices' => Brand::cases(),
                'choice_label' => fn(Brand $brand) => $brand->value,
                'placeholder' => 'Choose a brand',
            ])
            ->add('status', ChoiceType::class, [
                'choices' => PublicationStatus::cases(),
                'choice_label' => fn(PublicationStatus $status) => $status->value,
                'placeholder' => 'Choose a brand',
                'empty_data' => Brand::LENOVO,
            ])
            ->add('variants', CollectionType::class, [
                'entry_type' => VariantType::class,
                'allow_add' => true,
                'allow_delete' => true,
                'by_reference' => false,
                'label' => 'Variants',
                'entry_options' => ['label' => false],
            ]);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'data_class' => Product::class,
        ]);
    }
}