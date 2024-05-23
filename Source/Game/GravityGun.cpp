#include "GravityGun.h"

GravityGun::GravityGun(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void GravityGun::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)

    // not working // GravityManger = GetActor()->GetScene()->FindActor(TEXT("Camera"));
    
    GravityManger = GetActor()->GetScene()->FindActor(TEXT("GravityManger"))->GetScript(0);


    if (GravityManger == nullptr) {
        LOG(Info, "Could not find gravity Manger");
    }
    else
    {
        LOG(Info, "Gravity mmanger is found");
        GravityMangerptr = dynamic_cast<FakeGravityTest*>(GravityManger);
    }
}
//
void GravityGun::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void GravityGun::OnUpdate()
{
    // Here you can add code that needs to be called every frame

    if (Input::GetAction(String("Fire"))) {
        LOG(Info, "JustFired");
        PickObject();
    }

    if (Input::GetAction(String("AltFire"))) {
        LOG(Info, "Just alt Fired");
        PickGravityEndPoint();
    }
}


bool GravityGun::PickObject() {
    Vector3 startpoint = GetActor()->GetPosition();
    Vector3 ForwardVector = GetActor()->GetDirection();

    if (Physics::RayCast(startpoint, ForwardVector, Hit,CastDist,3,false)) {
        Actor* ObjectPtr = Hit.Collider->GetParent();
        if (ObjectPtr->GetType().ToString() == String("FlaxEngine.RigidBody")) {
            BodyPtr = dynamic_cast<RigidBody*>(ObjectPtr);
            if (BodyPtr->GetMass() < grab_strength && BodyPtr->GetEnableGravity() == true) {
                LOG(Info, "Grabbed thingy");
                //BodyPtr->AddForce(ForwardVector * BodyPtr->GetMass() * 300.0f, ForceMode::Impulse);
                BodyPtr->SetEnableGravity(false);
                GravityMangerptr->AddToIndex(BodyPtr, 'A');
                return true;
            }
            else { 
                BodyPtr = nullptr; 
                return false;
            }
            
        }
    }

    return false;
}

void GravityGun::PickGravityEndPoint() {
    Vector3 startpoint = GetActor()->GetPosition();
    Vector3 ForwardVector = GetActor()->GetDirection();

    if (Physics::RayCast(startpoint, ForwardVector, AltHit, CastDist, 3, false)) {
        Actor* ObjectPtr = AltHit.Collider->GetParent();
        if (ObjectPtr->GetType().ToString() == String("FlaxEngine.RigidBody")) {

        }
        else {
            GravityPullLoc = AltHit.Point;
            //LOG(Info, "Gravity Point is: {0}", GravityPullLoc);
            MakeVectors();

        }
    }

}

void GravityGun::MakeVectors() {
    if (BodyPtr != nullptr) {
        if (CastingType == 'A') {
            Vector3 NewGravityFoward = GravityPullLoc - BodyPtr->GetPosition();
            NewGravityFoward.Normalize();
            GravityMangerptr->NewGravityDir(NewGravityFoward, CastingType);
        }if (CastingType == 'P') {
            if (GravityPullLoc != (0.f, 0.f, 0.f)) {
                
                GravityMangerptr->NewGravityDir(GravityPullLoc, CastingType);
            }
            
        }
    }
}

