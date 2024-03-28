#include "PlayerControler_Body.h"

PlayerControler_Body::PlayerControler_Body(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function

    //PivCamraPiv = this->GetActor()->GetChild(TEXT("CamPiv"));

    _tickUpdate = true;
    _tickFixedUpdate = true;
}

void PlayerControler_Body::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
    //if (PlayerRigidBody == nullptr) { return; }
}

void PlayerControler_Body::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

//TODO//
// *Spring arm* //
// Need to add a spring arm to the player cam, the plan is to do a line trace and then move it along a ray cast with a lerp 
// to help it feel smooth on the jitter, Maybe if I can do a shape cast 

void PlayerControler_Body::OnUpdate()
{   
    if (CamraPiv == nullptr) { return; }

    this->GetActor()->SetPosition(PlayerRigidBody->GetPosition() + PlayerBodyOfset);

   // gets the input of mouse
    Float2 MousePoDelta = Float2(Input::GetAxis(String("Mouse X")), Input::GetAxis(String("Mouse Y"))) * MouseSenes;

    //rots first piv
    CamraPiv->SetOrientation(CamraPiv->GetTransform().Orientation.Euler(CamraPiv->GetTransform().Orientation.GetEuler().X, CamraPiv->GetTransform().Orientation.GetEuler().Y + MousePoDelta.X, 0.0f));
    
    //rots second and mackes sure that its only roting 85 degs // dose it ugly but w/e
    float tempx = SubPiv->GetTransform().Orientation.GetEuler().X + MousePoDelta.Y;

    if (tempx > 85.0f) {
        tempx = 85.0f;
    }
    if (tempx < -85.0f) {
        tempx = -85.0f;
    }
    SubPiv->SetOrientation(SubPiv->GetTransform().Orientation.Euler(tempx, SubPiv->GetTransform().Orientation.GetEuler().Y, 0.0f));


}

void PlayerControler_Body::OnFixedUpdate() {

    Input::GetAction(String(""));

}