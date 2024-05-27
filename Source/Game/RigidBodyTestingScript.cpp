#include "RigidBodyTestingScript.h"

RigidBodyTestingScript::RigidBodyTestingScript(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = false;
    _tickFixedUpdate = true;
}

void RigidBodyTestingScript::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)

}

void RigidBodyTestingScript::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void RigidBodyTestingScript::OnUpdate()
{
    // Here you can add code that needs to be called every frame
}

void RigidBodyTestingScript::OnFixedUpdate()
{
    // Here you can add code that needs to be called every frame
    if (testingbody == nullptr) { return; }

    elaspedtime = Time::GetDeltaTime() + elaspedtime;
    LOG(Info, "Time: {0}", elaspedtime);
    if (elaspedtime > 5.0f) {
        opengate[0] = true;
    }
    //opengate[0] = false;
    if (opengate[0] == true) {
        testingbody->AddTorque(Force, ForceMode::Impulse);
    }

    //SubPiv->SetOrientation(SubPiv->GetTransform().Orientation.Euler(tempx, SubPiv->GetTransform().Orientation.GetEuler().Y, 0.0f));
    if (int(elaspedtime) % 30 ==0) {
        //return;
        elaspedtime = elaspedtime + 1.0f;
        Float3 temp = Float3(testingbody->GetTransform().Orientation.GetEuler().X, testingbody->GetTransform().Orientation.GetEuler().Y+90.0f, testingbody->GetTransform().Orientation.GetEuler().Z);
        testingbody->SetOrientation(testingbody->GetTransform().Orientation.Euler(temp));
    }

}