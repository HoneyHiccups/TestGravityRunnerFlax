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
    // this is the horzantal piv
    CamraPiv->SetOrientation(CamraPiv->GetTransform().Orientation.Euler(CamraPiv->GetTransform().Orientation.GetEuler().X, CamraPiv->GetTransform().Orientation.GetEuler().Y + MousePoDelta.X, 0.0f));
    
    //rots second and mackes sure that its only roting 85 degs 
    float tempx = Math::Clamp<float>(SubPiv->GetTransform().Orientation.GetEuler().X + MousePoDelta.Y, -85.0f, 85.0f);

    SubPiv->SetOrientation(SubPiv->GetTransform().Orientation.Euler(tempx, SubPiv->GetTransform().Orientation.GetEuler().Y, 0.0f));


}

void PlayerControler_Body::OnFixedUpdate() {

    // needs to be fixed

    Vector2 InputDir =  Float2(Input::GetAxis(String("Vertical")), Input::GetAxis(String("Horizontal")));

    Vector3 MoveDir = Vector3(InputDir.X, 0.0f, InputDir.Y*-1.0f);
    //InputDir.Normalize();
    MoveDir.Normalize();
    ForwardVec = CamraPiv->GetTransform().GetForward();
    UpVec = CamraPiv->GetTransform().GetUp();

    //Need to get the angle so that we can rot, im not sure I think I am thinking about this wrong
    //WIll think while I sleep brain is tierd, as of now, the ball char for movment feels pretty alright, I do
    //Have consoners about the way it goses up slaps, atm it gose slower up sloops then walking and faster down
    //This both feels normal and also alian in games, I just need to make sure that it alawys feel approtie
    //Most of having a ball instead of feets will be about trying to make things feel approite when they dont
    //Annother thing that most likly needs to be added is step snapping, else we might get impact bounces
    //This was alawys going to need to be added, the big question I have though is this really saving time or imporivng
    //the player experiances im not sure, that is why I am testing and finding things could
    double angle;

    MoveDir = MoveDir * ForwardVec;
    MoveDir.Normalize();
    LOG(Info, "Forwad Vector: {0}", UpVec);
    if (InputDir != 0.0f) {
        PlayerRigidBody->AddTorque(MoveDir*3000000.0f, ForceMode::Impulse);
        LOG(Info,"{0}", MoveDir);
    }
    
   
    
}