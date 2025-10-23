<?php
namespace App\Form;

use App\Entity\Variant;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\Extension\Core\Type\ChoiceType;
use Symfony\Component\Form\Extension\Core\Type\TextType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;

class VariantType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder
            ->add('type', ChoiceType::class, [
                'choices' => [
                    'Brand' => 'brand',
                    'Disk Capacity' => 'diskCapacity',
                    'Screen Size' => 'screenSize',
                    'Keyboard Type' => 'keyboardType',
                    'Status' => 'status',
                ],
            ])
            ->add('value', ChoiceType::class, [
                'choices' => [
                    'Apple' => 'apple',
                    'Lenovo' => 'lenovo',
                    'MSI' => 'msi',
                    'Qwerty' => 'qwerty',
                    'Azerty' => 'azerty',
                    '1TB' => '1tb',
                    '2TB' => '2tb',
                    '14' => '14',
                    '15' => '15',
                    '16' => '16',
                    '17' => '17',
                    'Draft' => 'draft',
                    'Published' => 'published',
                    'Archived' => 'archived',
                ],
                'label' => 'Value',
                'placeholder' => 'Choose an option',
            ]);
    }

    public function configureOptions(OptionsResolver $resolver)
    {
        $resolver->setDefaults([
            'data_class' => Variant::class,
        ]);
    }
}