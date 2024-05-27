#include "ThirdPersonPlayerContoller.h"
ThirdPersonPlayerContoller::ThirdPersonPlayerContoller(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
    _tickFixedUpdate = true;
}

void ThirdPersonPlayerContoller::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
    BaseLinearDamping = RigidBody->GetLinearDamping();
    if (GetActor()->GetScene()->FindActor(TEXT("GravityManger"))) {
        GravityManger = dynamic_cast<FakeGravityTest*>(GetActor()->GetScene()->FindActor(TEXT("GravityManger"))->GetScript(0));
        GravityManger->SetPlayerRef(RigidBody);
    }

}

void ThirdPersonPlayerContoller::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)

}


void ThirdPersonPlayerContoller::Levitate() {
    b_body_orient_gravity = true;
    bodytwistspeed = 1.0f;
    RigidBody->SetEnableGravity(false);
    targetdamping = 30.0f;
    BodyAimOrent = Quaternion::LookRotation(PlayerCam->GetTransform().GetForward(), PlayerCam->GetTransform().GetUp());
    //BodyHolder->SetOrientation(Quaternion::LookRotation(PlayerCam->GetTransform().GetForward(), PlayerCam->GetTransform().GetUp()));
    
    if (bgrounded == true) {
        bodytwistspeed = 7.0f;
        RigidBody->AddForce((GravityDir * (-850.0f * RigidBody->GetMass())), ForceMode::Impulse);
    }
    
}

void ThirdPersonPlayerContoller::AugFalling(Vector3 pickdir){
    if (GravityManger != nullptr) {
        b_body_orient_gravity = true;


        if (pickdir == Vector3::Zero) {
            Vector3 NewDir = BodyHolder->GetPosition() - EndPoint->GetPosition();
            NewDir.Normalize();
            GravityDir = NewDir;
            BodyHolder->SetPosition(RigidBody->GetPosition() + (GravityDir * -45.0f));

            BodyAimOrent = Quaternion::LookRotation(PlayerCam->GetTransform().GetUp(), (GravityDir * -1.0f));
        }
        else {
            GravityDir = pickdir;
            BodyHolder->SetPosition(RigidBody->GetPosition() + (GravityDir * -45.0f));
            //gravity dir should be the new up vector of the camrea rig 
            //we need to come up with a with a way of taking the player forward vector and projecting it into a plane that
            //is perpdicular to gravity dir then we can rotate object by normal 

            //should also be abale to rot cam with just up vector, and let math decided forward vbector.
            
            HorzialtalPlane = Maths::VectorPlaneShift(GravityDir, HPiv->GetTransform().GetLeft());

            LookAtCube->SetPosition(HPiv->GetPosition() + (HorzialtalPlane * 500.0f));//debug

            BodyAimOrent = Quaternion::LookRotation(HorzialtalPlane, (GravityDir * -1.0f));
            BodyHolder->SetOrientation(Quaternion::LookRotation(HorzialtalPlane, (GravityDir * -1.0f)));
            


            HPiv->SetOrientation(Quaternion::LookRotation(HorzialtalPlane/*need forward*/, GravityDir * -1.0f));
        }
  
        targetdamping = BaseLinearDamping;
        RigidBody->SetLinearDamping(BaseLinearDamping);
        
        GravityManger->SetPlayerPlayerGravity(GravityDir);
        
    }
}
////
void ThirdPersonPlayerContoller::UnLevitate() {
    b_body_orient_gravity = false;
    RigidBody->SetEnableGravity(true);
    targetdamping = BaseLinearDamping;
    RigidBody->SetLinearDamping(BaseLinearDamping);
    GravityDir = Vector3(0.0f, -1.0f, 0.0f);
    bodytwistspeed = 7.0f;
    GravityManger->SetPlayerPlayerGravity(GravityDir);
    //need a more robust solution
    BodyAimOrent = Quaternion::Euler(0.0f, 1.0f, 0.0f);

    HorzialtalPlane = Maths::VectorPlaneShift(GravityDir, Vector3(0, 0, 1));

    //BodyHolder->SetOrientation(Quaternion::GetRotationFromTo(BodyHolder->GetTransform().GetUp(), GravityDir, BodyHolder->GetTransform().GetDown()));
}
//
void ThirdPersonPlayerContoller::OnUpdate()
{


    Screen::SetCursorLock(CursorLockMode::Locked);
    Screen::SetCursorVisible(false);

    
    BodyHolder->SetPosition(RigidBody->GetPosition() + (GravityDir * -45.0f));
    //CamRig->SetPosition(Math::LerpStable(CamRig->GetPosition(), BodyHolder->GetPosition(),Math::Clamp(Time::GetDeltaTime()*20.0f, 0.0f,1.0f)));
    CamRig->SetPosition(BodyHolder->GetPosition());


    // Camrea look
    Input = Vector2(Input::GetAxis(String("Mouse X")), Input::GetAxis(String("Mouse Y")));
    Input = Input * lookSens;
    CamreaRotStack = CamreaRotStack - Input;

    Vector3 horlock = Vector3(0, -1, 0);
    Vector3 VertLock = Vector3(1, 0, 0);

    Quaternion Vertpiv; Quaternion::RotationAxis(VertLock, Input.Y, Vertpiv);
    Quaternion Horzpiv; Quaternion::RotationAxis(horlock, Input.X*-1.0f, Horzpiv);
    
    
    //this is almost working need to think about things.
    
    Vertpiv = Vertpiv * VPiv->GetLocalOrientation();
    Horzpiv = Horzpiv * HPiv->GetOrientation();
    
    VPiv->SetLocalOrientation(Vertpiv);
   // VPiv->SetOrientation(Vertpiv);
    HPiv->SetOrientation(Horzpiv);
    
    
    //old rot system
    /*
    HPiv->SetOrientation(HPiv->GetOrientation().Euler(0.0f, HPiv->GetOrientation().GetEuler().Y + Input.X, 0.0f));
    VPiv->SetOrientation(VPiv->GetOrientation().Euler(Math::Clamp(VPiv->GetOrientation().GetEuler().X + Input.Y,-86.0f,86.0f), HPiv->GetOrientation().GetEuler().Y, 0.0f));

    */
    Vector3 temp = PlayerCam->GetTransform().GetBackward();
    temp.Normalize();
    
    //spring arm
    if (Physics::SphereCast(BodyHolder->GetPosition(), 5.0f, temp, SpringArmHitR, 500.0f, 1, false)) {
        CamTargetLoc = Math::Lerp<Vector3, float>(VPiv->GetPosition(), EndPoint->GetPosition(), Math::Clamp<float>((SpringArmHitR.Distance / 500.0f), 0.22f, 1.0f));

    }
    else {
        CamTargetLoc = EndPoint->GetPosition();
    }
}



void ThirdPersonPlayerContoller::OnFixedUpdate()
{
 


    Vector2 InputDir = Float2(Input::GetAxis(String("Vertical")), Input::GetAxis(String("Horizontal")));
    if (InputDir != 0.0f) {
        WishDir = (HPiv->GetTransform().GetForward() * -InputDir.Y) + (HPiv->GetTransform().GetRight() * InputDir.X);
        WishDir.Normalize();
        RigidBody->AddTorque(WishDir * MaxTorq, ForceMode::Impulse);
        

    }
    else {
        WishDir = 0.0f;
    }
    RigidBody->SetAngularVelocity(0.0f);
    
    IsPlayerGrounded();
    InputStack();

    tickindex = tickindex + 1;
    if (tickindex == 10) {
        tickindex = 0;
        tick10th();
    }

    if(true) {


        // cuss the player can better understand how to orinet to gravity we can now understand use player forward vector to created horzailtal plane
        Vector3 PlayerMov = RigidBody->GetLinearVelocity();
        PlayerMov.Normalize();
        Vector3 horzplan = Forceinverston(GravityDir);
        Vector3 VelocityProjection = RigidBody->GetLinearVelocity();
        VelocityProjection.Normalize();
        VelocityProjection = horzplan * VelocityProjection;
        PlayerLookAtBall->SetPosition(BodyHolder->GetPosition() + VelocityProjection * 3000.0f);
        if(RigidBody->GetLinearVelocity().Length() > 10.0f && b_body_orient_gravity == false)
        { 
            
            BodyHolder->LookAt(PlayerLookAtBall->GetPosition(), (GravityDir*-1.0f));
            //PlayerFace->LookAt(PlayerFace->GetPosition() + (PlayerMov * 300.0f), (GravityDir * -1.0f));
        }

        
    }
    //


    if (b_body_orient_gravity == true) {
        Quaternion newornt; 
        Quaternion::Slerp(BodyHolder->GetTransform().Orientation, BodyAimOrent, Time::GetDeltaTime()* bodytwistspeed, newornt);
        BodyHolder->SetOrientation(newornt);

    }

    if (openrezjumpcd == true) {
        timmerticks[1] = timmerticks[1] - Time::GetDeltaTime();
        if (timmerticks[1] <= 0) {
            timmerticks[1] = .07;
            openrezjumpcd = false;
            bcanjump = true;

        }
    }
    lindampingMod();
    
}

void ThirdPersonPlayerContoller::CameraAttached(Camera* cam) {
    PlayerCam = cam;
}

// depracate soon
Vector3 ThirdPersonPlayerContoller::Forceinverston(Vector3& v) {
    if (v.IsNormalized()) {
        Vector3 inverted_v = inverted_v.Abs(v);
        inverted_v.X = 1.0f - inverted_v.X; 
        inverted_v.Y = 1.0f - inverted_v.Y; 
        inverted_v.Z = 1.0f - inverted_v.Z;
        inverted_v.Normalize();
        return inverted_v;
    }
    else {
        return v;
    }

}

void ThirdPersonPlayerContoller::Jump() {
    if (bcanjump == true) {
        bcanjump = false;
        RigidBody->AddForce((GravityDir * (Jumpz + RigidBody->GetMass()) * -1.0f), ForceMode::Impulse);
    }
    
    
}

void ThirdPersonPlayerContoller::InputStack()
{
    if (Input::GetAction(String("Lev"))) {
        if (LevButton == false) {
            LevButton = true;

            LevState = LevState + 1;
            if (LevState > 2) {
                LevState = 1;
            }
            // Add logic here

            if (LevState == 1) {
                Levitate();
            }
            else {
                AugFalling(Vector3::Zero);
            }

            //


        }
    }
    else {
        LevButton = false;
    }

    if (Input::GetAction(String("UnLev"))) {
        if (UnlevButton == false) {
            UnlevButton = true;

            LevState = 0;
            // Add logic here
            UnLevitate();
            //            
        }
    }
    else {
        UnlevButton = false;
    }

    if (Input::GetAction(String("JumpButton"))) 
    {
        if (jumpbuttun == false) 
        {
            jumpbuttun = true;
            Jump();
            
        }

    }
    else {
        jumpbuttun = false;
    }
}

void ThirdPersonPlayerContoller::IsPlayerGrounded() {
    if (Physics::SphereCast(RigidBody->GetPosition(), 15.0f, GravityDir, IsGroundedSweep, 20.0f, 1, false)) {
        bgrounded = true;
        if (justlanded == false && bgrounded == true) {
            justlanded = true;
            JustLanded();
        }


        return;
    }
    bgrounded = false;
    justlanded = false;
    return;

}


Float3 ThirdPersonPlayerContoller::GetFaceNormal() {
    RayCasterFromFeetToMakePlane();
    Vector3 temp = WorkingPlaneStruct.GetUp()*-1.0f;
    temp.Normalize();
    return temp;

} 


void ThirdPersonPlayerContoller::lindampingMod() {
    if (targetdamping > 1 && RigidBody->GetLinearDamping()<30.0) {
        timmerticks[0] = timmerticks[0] + Time::GetDeltaTime()*.5;
        RigidBody->SetLinearDamping(   Math::Clamp(Math::Lerp(BaseLinearDamping, targetdamping, timmerticks[0]),1.1f,30.0f )  );
        if (RigidBody->GetLinearDamping() == 30.0f) {
            RigidBody->SetLinearVelocity(Vector3::Zero);
        }
    }
    else {
        timmerticks[0] = 0.0;
    }
        
}

void ThirdPersonPlayerContoller::JustLanded() {
    openrezjumpcd = true;
    AugFalling(GetFaceNormal());

}


// a problem is that it dose not grab the right normal everytime
// we can use dot product and hit normal to test if we need to run the math again
//try to find why it fails the first time
void ThirdPersonPlayerContoller::RayCasterFromFeetToMakePlane() {
    RayCastHit hit;
    float dist = 1000.0f;
    Vector3 CastDir = IsGroundedSweep.Point - RigidBody->GetPosition();
    CastDir.Normalize();
    

    if (Physics::RayCast(RayCaster1->GetPosition(), GravityDir, hit, dist, 1, false)) {
        WorkingPlaneStruct.WorldPostionA =  hit.Point;

    }
    if (Physics::RayCast(RayCaster2->GetPosition(), GravityDir, hit, dist, 1, false)) {
        WorkingPlaneStruct.WorldPostionB = hit.Point;

    }
    if (Physics::RayCast(RayCaster3->GetPosition(), GravityDir, hit, dist, 1, false)) {
        WorkingPlaneStruct.WorldPostionC = hit.Point;

    }
    WorkingPlaneStruct.__MakePlane();

}

void ThirdPersonPlayerContoller::tick10th() {
    RayCastHit testing;
    RayCasterFromFeetToMakePlane();
    Physics::RayCast(RayCaster1->GetPosition(), GravityDir, testing, 100.0f, 1, false);
    LOG(Info, "The Dot of hit and gravity is: {0}", Vector3::Dot(testing.Normal, WorkingPlaneStruct.GetUp()));
    
}