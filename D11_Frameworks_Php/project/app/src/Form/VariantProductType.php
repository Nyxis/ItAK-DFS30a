<?php

namespace App\Form;

use App\Entity\VariantProduct;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\Extension\Core\Type\ChoiceType;
use Symfony\Component\Form\Extension\Core\Type\IntegerType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;

class VariantProductType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder
            ->add('screenSize', ChoiceType::class, [
                'choices' => [
                    '14"' => 14,
                    '15"' => 15,
                    '16"' => 16,
                    '17"' => 17,
                ],
            ])
            ->add('hdCapacity', IntegerType::class, [
                'label' => 'Capacité du disque dur (Go)'
            ])
            ->add('keyboardType', ChoiceType::class, [
                'choices' => [
                    'AZERTY' => 'AZERTY',
                    'QWERTY' => 'QWERTY',
                ],
            ]);
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'data_class' => VariantProduct::class,
        ]);
    }
}
