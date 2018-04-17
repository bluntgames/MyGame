
#pragma once

#include <AzCore/Component/Component.h>

#include <MyGame/MyGameBus.h>

namespace MyGame
{
    class MyGameSystemComponent
        : public AZ::Component
        , protected MyGameRequestBus::Handler
    {
    public:
        AZ_COMPONENT(MyGameSystemComponent, "{D43903E9-A1D5-4621-830F-D014A56BA3FD}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

    protected:
        ////////////////////////////////////////////////////////////////////////
        // MyGameRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };
}
