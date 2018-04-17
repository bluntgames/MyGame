#pragma once

#include <AzCore/Component/Component.h>

namespace MyGame
{
    class MyGameComponent : public AZ::Component
    {
    public:
        AZ_COMPONENT( MyGameComponent, "{088D8771-74AE-4E82-B774-37EF869FAE95}" );

        // AZ::Component interface implementation.
        void Init() override {}
        void Activate() override {}
        void Deactivate() override {}

        // Required Reflect function.
        static void Reflect( AZ::ReflectContext* context );

        // Optional functions for defining provided and dependent services.
        static void GetProvidedServices( AZ::ComponentDescriptor::DependencyArrayType& provided );
        static void GetDependentServices( AZ::ComponentDescriptor::DependencyArrayType& dependent );
        static void GetRequiredServices( AZ::ComponentDescriptor::DependencyArrayType& required );
        static void GetIncompatibleServices( AZ::ComponentDescriptor::DependencyArrayType& incompatible );

    private:
        enum class SomeEnum
        {
            EnumValue1,
            EnumValue2,
        };

        float m_someFloatField;
        AZStd::string m_someStringField;
        SomeEnum m_someEnumField;
        //AZStd::vector<SomeClassThatSomeoneHasReflected> m_things;

        int m_runtimeStateNoSerialize;
    };
}