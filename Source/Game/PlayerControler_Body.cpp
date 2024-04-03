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
    BaseAngleDamp = PlayerRigidBody->GetAngularDamping();
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
    // this is the horzantal piv
    CamraPiv->SetOrientation(CamraPiv->GetTransform().Orientation.Euler(CamraPiv->GetTransform().Orientation.GetEuler().X, CamraPiv->GetTransform().Orientation.GetEuler().Y + MousePoDelta.X, 0.0f));
    
//    Vector3 Lookat = PlayerRigidBody->GetLinearVelocity();
//    Lookat.Normalize();
//    Lookat = Lookat * 1220.0f;
//    Lookat = PlayerMeshHolder->GetPosition() + Lookat;   
//    PlayerMeshHolder->LookAt(Lookat);
    
    PlayerMeshHolder->SetOrientation(CamraPiv->GetOrientation());

    //rots second and mackes sure that its only roting 85 degs 
    float tempx = Math::Clamp<float>(SubPiv->GetTransform().Orientation.GetEuler().X + MousePoDelta.Y, -85.0f, 85.0f);

    SubPiv->SetOrientation(SubPiv->GetTransform().Orientation.Euler(tempx, SubPiv->GetTransform().Orientation.GetEuler().Y, 0.0f));


}

void PlayerControler_Body::OnFixedUpdate() {

    // needs to be fixed

    Vector2 InputDir =  Float2(Input::GetAxis(String("Vertical")), Input::GetAxis(String("Horizontal")));

    RightVec = InputDir.Y * CamraPiv->GetTransform().GetForward() *-1.0f; // I know I am getting forward vec butt cuss feet are ball this is what is needed
    ForwardVec = InputDir.X * CamraPiv->GetTransform().GetRight();
    WishDir = ForwardVec + RightVec;
    WishDir.Normalize();

    if (InputDir != 0.0f)// the if is not needed but maybe I want to tag somthing onto this when like a haulting thing
        { //Just a sample of idea, maybe use what the liner velocity vec is and dot it to get a damping scaler to make the movent feel more twitchy
        //PlayerRigidBody->SetAngularDamping(BaseAngleDamp * 0.01f);
        PlayerRigidBody->AddTorque((WishDir) *3000000.0f, ForceMode::Impulse);
    }
    else {
        //PlayerRigidBody->SetAngularDamping(BaseAngleDamp * 100.0f);
    }
    
   
    
}