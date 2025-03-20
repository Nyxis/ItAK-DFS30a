<?php

namespace App\Form;

use App\Entity\Product;
use App\Form\VariantProductType;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\Extension\Core\Type\ChoiceType;
use Symfony\Component\Form\Extension\Core\Type\CollectionType;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;
use Symfony\Component\Form\FormEvent;
use Symfony\Component\Form\FormEvents;
use Symfony\Component\Validator\Constraints\NotBlank;

class ProductFormType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->add('name', null, ['constraints' => [new NotBlank()]])
            ->add('brand', ChoiceType::class, [
                'choices' => [
                    'Apple' => 'Apple',
                    'Lenovo' => 'Lenovo',
                    'MSI' => 'MSI',
                ],
                'constraints' => [new NotBlank()]
            ])
            ->add('status', ChoiceType::class, [
                'choices' => [
                    'Draft' => 'draft',
                    'Published' => 'published',
                    'Archived' => 'archived',
                ],
            ])
            ->add('variants', CollectionType::class, [
                'entry_type' => VariantProductType::class,
                'allow_add' => true,
                'allow_delete' => true,
                'prototype' => true,
                'label' => 'Variantes',
                'attr' => ['class' => 'variant-collection']
            ])
            ->add('save', SubmitType::class);

    }

    // pas eu le temps de terminer
    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'data_class' => Product::class,
        ]);
    }
}
