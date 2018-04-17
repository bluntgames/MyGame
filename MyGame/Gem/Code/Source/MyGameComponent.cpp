#include "MyGame_precompiled.h"

#include "MyGameComponent.h"
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>

namespace MyGame
{
    void MyGameComponent::Reflect( AZ::ReflectContext* context )
    {
        AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>( context );
        if ( serialize )
        {
            // Reflect the class fields that you want to serialize.
            // In this example, m_runtimeStateNoSerialize is not reflected for serialization.
            // Base classes with serialized data should be listed as additional template
            // arguments to the Class< T, ... >() function.
            serialize->Class<MyGameComponent, AZ::Component>()
                ->Version( 1 )
                ->Field( "SomeFloat",   &MyGameComponent::m_someFloatField )
                ->Field( "SomeString",  &MyGameComponent::m_someStringField )
                //->Field( "Things",      &MyGameComponent::m_things )
                ->Field( "SomeEnum",    &MyGameComponent::m_someEnumField );

            AZ::EditContext* edit = serialize->GetEditContext();
            if ( edit )
            {
                edit->Class<MyGameComponent>( "My Game Component", "The World's Most Clever Component" )
                    ->ClassElement( AZ::Edit::ClassElements::EditorData, "" )
                    ->Attribute( AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC( "Game" ) )
                    ->DataElement( AZ::Edit::UIHandlers::Default, &MyGameComponent::m_someFloatField, "Some Float", "This is a float that means X." )
                    ->DataElement( AZ::Edit::UIHandlers::Default, &MyGameComponent::m_someStringField, "Some String", "This is a string that means Y." )
                    ->DataElement( AZ::Edit::UIHandlers::ComboBox, &MyGameComponent::m_someEnumField, "Choose an Enum", "Pick an option among a set of enum values." )
                    ->EnumAttribute( MyGameComponent::SomeEnum::EnumValue1, "Value 1" )
                    ->EnumAttribute( MyGameComponent::SomeEnum::EnumValue2, "Value 2" )
                    //->DataElement( AZ::Edit::UIHandlers::Default, &MyGameComponent::m_things, "Bunch of Things", "A list of things for doing Z." )
                    ;
            }
        }
    }

    /*static*/ 
    void MyGameComponent::GetProvidedServices( AZ::ComponentDescriptor::DependencyArrayType& provided )
    {
        //provided.push_back( AZ_CRC( "ProvidedService" ) );
        //provided.push_back( AZ_CRC( "AnotherProvidedService" ) );
    }

    /*static*/
    void MyGameComponent::GetRequiredServices( AZ::ComponentDescriptor::DependencyArrayType& required )
    {
        //required.push_back( AZ_CRC( "RequiredService" ) );
        //required.push_back( AZ_CRC( "AnotherRequiredService" ) );
    }

    /*static*/
    void MyGameComponent::GetIncompatibleServices( AZ::ComponentDescriptor::DependencyArrayType& incompatible )
    {
        //incompatible.push_back( AZ_CRC( "IncompatibleService" ) );
    }

    /*static*/
    void MyGameComponent::GetDependentServices( AZ::ComponentDescriptor::DependencyArrayType& dependent )
    {
        //dependent.push_back( AZ_CRC( "DependentOnService" ) );
    }
}