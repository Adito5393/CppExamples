///////////////////////////////////////////////////////////////////////////////"
//
//  Copyright PHOENIX CONTACT Electronics GmbH
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "COMP_NotificationsProgramProvider.hpp"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

#include "Arp/Plc/Commons/Domain/PlcState.hpp"
#include "Arp/System/Nm/NotificationManager.hpp"
#include "Arp/System/NmPayload/Plc/PlcStateChangedPayload.hpp"
#include "Arp/System/NmPayload/Device/NetworkConfigurationChangedPayload.hpp"
#include "ExamplePayload.hpp"

namespace NotificationExample
{

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//#component
class COMP_Notifications : public ComponentBase, public ProgramComponentBase, private Loggable<COMP_Notifications>
{
public: // typedefs

public: // construction/destruction
    COMP_Notifications(IApplication& application, const String& name);
    virtual ~COMP_Notifications() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    COMP_Notifications(const COMP_Notifications& arg) = delete;
    COMP_Notifications& operator= (const COMP_Notifications& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // SubscriptionCallbacks
    void NM_Subscription1_Callback(const Arp::System::Nm::Notification& notification);
    void NM_Subscription2_Callback(const Arp::System::Nm::Notification& notification);
    void NetworkConfigurationChanged_Callback(const Arp::System::Nm::Notification& notification);
    void PlcStateChanged_Callback(const Arp::System::Nm::Notification& notification);


private: // fields
    COMP_NotificationsProgramProvider programProvider;

    Arp::System::Nm::NotificationManager&   nm = NotificationManager::GetInstance();
    Arp::System::Nm::NotificationSubscriber Custom_subscription;
    Arp::System::Nm::NotificationSubscriber Custom_subscription2;
    Arp::System::Nm::NotificationSubscriber NetworkConfigurationChanged_subscription;
    Arp::System::Nm::NotificationSubscriber PlcStateChanged_subscription;


public: /* Ports
           =====
           Component ports are defined in the following way:

           //#attributes(Hidden)
           struct Ports
           {
               //#name(NameOfPort)
               //#attributes(Input|Retain|Opc)
               Arp::boolean portField = false;
               // The GDS name is "<componentName>/NameOfPort" if the struct is declared as Hidden
               // otherwise the GDS name is "<componentName>/PORTS.NameOfPort"
           };

           //#port
           Ports ports;

           Create one (and only one) instance of this struct.
           Apart from this single struct instance, there must be no other Component variables declared with the #port comment.
           The only attribute that is allowed on the struct instance is "Hidden", and this is optional.
           The struct can contain as many members as necessary.
           The #name comment can be applied to each member of the struct, and is optional.
           The #name comment defines the GDS name of an individual port element. If omitted, the member variable name is used as the GDS name.
           The members of the struct can be declared with any of the attributes allowed for a Program port.
        */
       int OP_uiValue1{};
       int OP_uiValue2{};
};

inline IComponent::Ptr COMP_Notifications::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new COMP_Notifications(application, name));
}

} // end of namespace NotificationExample
