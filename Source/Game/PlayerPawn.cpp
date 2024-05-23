#include "PlayerPawn.h"

PlayerPawn::PlayerPawn(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
    _tickFixedUpdate = true;
}

void PlayerPawn::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void PlayerPawn::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void PlayerPawn::OnUpdate()
{
    Screen::SetCursorLock(CursorLockMode::Locked);
    Screen::SetCursorVisible(false);
    
    //CamRig->SetPosition(RigidBody->GetPosition());
    CamRig->SetPosition(Math::LerpStable(CamRig->GetPosition(), RigidBody->GetPosition(), Math::Clamp<float>(Time::GetDeltaTime()*150.0f,0.0f,1.0f )));
    BodyHolder->SetPosition(CamRig->GetPosition());

    Input = Vector2(Input::GetAxis(String("Mouse X")), Input::GetAxis(String("Mouse Y")));
    Input = Input * lookSens;

    HPiv->SetOrientation(HPiv->GetOrientation().Euler(0.0f, HPiv->GetOrientation().GetEuler().Y + Input.X, 0.0f));
    VPiv->SetOrientation(VPiv->GetOrientation().Euler(VPiv->GetOrientation().GetEuler().X + Input.Y, HPiv->GetOrientation().GetEuler().Y, 0.0f));

    //spring arm
    if (Physics::SphereCast(RigidBody->GetPosition(), 5.0f, VPiv->GetTransform().GetBackward(), SpringArmHitR, 450.0f, 1, false)) {
        CamTargetLoc = Math::Lerp<Vector3,float>(VPiv->GetPosition(), EndPoint->GetPosition(), Math::Clamp<float>((SpringArmHitR.Distance / 450.0f),0.22f,1.0f) );

    }
    else {
        CamTargetLoc = EndPoint->GetPosition();
    }

    
}

void PlayerPawn::OnFixedUpdate() {
    Vector2 InputDir = Float2(Input::GetAxis(String("Vertical")), Input::GetAxis(String("Horizontal")));
    if (InputDir != 0.0f) {
        WishDir = (HPiv->GetTransform().GetForward() * InputDir.X) + (HPiv->GetTransform().GetRight() * InputDir.Y);
        WishDir.Normalize();
        RigidBody->AddForce(WishDir * MaxMoveSpeed , ForceMode::Impulse);

    }
    else {
        WishDir = 0.0f;
    }
    
}

void PlayerPawn::CameraAttached(Camera* cam) {
    PlayerCam = cam;
}
//