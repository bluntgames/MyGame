
#include "MyGame_precompiled.h"
#include <platform_impl.h>

#include <AzCore/Memory/SystemAllocator.h>

#include "MyGameSystemComponent.h"
#include "MyGameComponent.h"

#include <IGem.h>

namespace MyGame
{
    class MyGameModule
        : public CryHooksModule
    {
    public:
        AZ_RTTI(MyGameModule, "{A457F704-466D-4F21-B564-95140C78E71D}", CryHooksModule);
        AZ_CLASS_ALLOCATOR(MyGameModule, AZ::SystemAllocator, 0);

        MyGameModule()
            : CryHooksModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyGameSystemComponent::CreateDescriptor(),
                MyGameComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyGameSystemComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(MyGame_9d225f763544464baafa95e2a88bbec5, MyGame::MyGameModule)
