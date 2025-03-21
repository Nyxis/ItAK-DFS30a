<?php
namespace App\Form;

use App\Entity\Product;
use App\Entity\VariantProduit;
use App\Enum\Brand;
use App\Enum\KeyBoardType;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\Extension\Core\Type\ChoiceType;
use Symfony\Component\Form\Extension\Core\Type\EnumType;
use Symfony\Component\Form\Extension\Core\Type\IntegerType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\Form\FormEvent;
use Symfony\Component\Form\FormEvents;
use Symfony\Component\Form\FormInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;
use Symfony\Component\Validator\Constraints\GreaterThanOrEqual;

class VariantType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options): void
    {
        $builder->add('keyboardType', EnumType::class, [
            'class' => KeyBoardType::class,
            'choice_label' => fn(KeyBoardType $type) => $type->value,
        ]);

        $builder->addEventListener(FormEvents::PRE_SET_DATA, function (FormEvent $event) {
            $form = $event->getForm();
            $parentForm = $form->getParent();
            $product = $parentForm?->getData();


            $screenSizes = [15, 17]; // Default for Lenovo/MSI
            $hdOptions = ['constraints' => []];

            if ($product instanceof Product) {
                $screenSizes = match ($product->getBrand()) {
                    Brand::APPLE => [14, 16],
                    default => [15, 17],
                };

                if ($product->getBrand() === Brand::MSI) {
                    $hdOptions['constraints'][] = new GreaterThanOrEqual(2000);
                }
            }

            $form->add('screenSize', ChoiceType::class, [
                'choices' => array_combine($screenSizes, $screenSizes),
                'placeholder' => 'Choose screen size',
            ]);

            $form->add('hdCapacity', IntegerType::class, array_merge([
                'label' => 'HD Capacity (GB)',
                'attr' => ['min' => 0]
            ], $hdOptions));
        });

        $builder->addEventListener(FormEvents::SUBMIT, function (FormEvent $event) {
            /** @var VariantProduit $variant */
            $variant = $event->getData();
            $form = $event->getForm();
            /** @var Product $product */
            $product = $form->getRoot()->getData();

            // Generate SKU
            $brandCode = strtoupper(substr($product->getBrand()->value, 0, 3));
            $kbCode = $variant->keyboardType === KeyBoardType::AZERTY ? 'AZ' : 'QW';
            $sku = sprintf(
                '%s-%d-%s-%d',
                $brandCode,
                $variant->screenSize,
                $kbCode,
                $variant->hdCapacity
            );

            // Create new variant with product association
            $event->setData(new VariantProduit(
                $sku,
                $variant->hdCapacity,
                $variant->screenSize,
                $variant->keyboardType,
                $product
            ));
        });
    }

    public function configureOptions(OptionsResolver $resolver): void
    {
        $resolver->setDefaults([
            'data_class' => VariantProduit::class,
            'empty_data' => function (FormInterface $form) {
                return new VariantProduit(
                    '', // Temporary empty SKU
                    (int) $form->get('hdCapacity')->getData(),
                    (int) $form->get('screenSize')->getData(),
                    $form->get('keyboardType')->getData(),
                    $form->getRoot()->getData()
                );
            },
        ]);
    }
}
