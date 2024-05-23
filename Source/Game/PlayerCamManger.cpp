#include "PlayerCamManger.h"

PlayerCamManger::PlayerCamManger(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void PlayerCamManger::OnEnable()
{


    // Here you can add code that needs to be called when script is enabled (eg. register for events)
    if (this->GetActor()->GetParent()->GetParent()->FindActor(String("BallPlayerCon")) ) {
        PlayerController = dynamic_cast<ThirdPersonPlayerContoller*>( this->GetActor()->GetParent()->GetParent()->FindActor(String("BallPlayerCon"))->GetScript(0) );
        PlayerController->CameraAttached(dynamic_cast<Camera*>(GetActor()));

    }
}

void PlayerCamManger::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void PlayerCamManger::OnUpdate()
{
    if (PlayerController == nullptr) {
        return;
    }

    if (laggycam == true) {
        float lerpPower = Vector3::Distance(GetActor()->GetPosition(), PlayerController->CamTargetLoc);
        lerpPower = Math::Clamp<float>(lerpPower / 2, 0.0f, 200.0f);
        GetActor()->SetPosition(Math::LerpStable<Vector3>(GetActor()->GetPosition(), PlayerController->CamTargetLoc, Time::GetDeltaTime() * lerpPower));

    }
    else {
        GetActor()->SetPosition(PlayerController->CamTargetLoc);
    }

    GetActor()->SetOrientation(PlayerController->VPiv->GetOrientation());

}
