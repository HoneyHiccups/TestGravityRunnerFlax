#include "FakeGravityTest.h"

FakeGravityTest::FakeGravityTest(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickFixedUpdate = true;
}

void FakeGravityTest::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
    if (Test != nullptr) {
        AOEBODYS[0] = Test;
        AOEBODYS[0]->SetEnableGravity(false);
    }


}

void FakeGravityTest::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void FakeGravityTest::OnFixedUpdate()
{
    currenttime += Time::GetDeltaTime();
   // LOG(Info, "The time is: {0}", currenttime);
   //LOG(Info, "The Frame time is: {0}", Time::GetDeltaTime());

    if (_switch0 == tickinterval) {
        //Body->AddForce((GravityDir * (Body->GetMass() * float(tickinterval))), ForceMode::Force);
        _switch0 = 0;
        //LOG(Info, "Force");

        //here we send it to the loop to effect the gravity of all objects for the aoe
        //the hope is that we can use this to make the objects around the player that worp gravity get effect
        SimulateGravityAOE();
        // due to how this is mostly a cosmetic thing we run it on a lower tick rate Ie the tick interval and scale to force so it acts normal

    }
    else {
        _switch0 = _switch0 + 1;
    }


}

bool FakeGravityTest::AddToIndex(ScriptingObjectReference<RigidBody> bodyref, char type) {
    if (AOELISTINDEX >= 999) { return false; }
    
    if (type == 'A') {
        AOELISTINDEX = AOELISTINDEX + 1;
        for (int i = 0; i < 999; i++) {
            if (AOEBODYS[i] == nullptr) {
                AOEBODYS[i] = bodyref;
                AOEBODYS[i]->SetEnableGravity(false);
                //LOG(Info, "Jsut added body with type A: {0}", AOEBODYS[i]->GetName());
                return true;
            }
        }
    }

    if (type == 'P') {
        AOELISTINDEX = AOELISTINDEX + 1;
        for (int i = 0; i < 999; i++) {
            if (AOEBODYS[i] == nullptr) {
                AOEBODYS[i] = bodyref;
                AOEBODYS[i]->SetEnableGravity(false);
                //LOG(Info, "Jsut added body with type P: {0}", AOEBODYS[i]->GetName());
                return true;
            }
        }
    }
    return false;
}

void FakeGravityTest::SimulateGravityAOE() {
    if (CurrentType == 'A') {
        for (int i = 0; i < 999; i++) {
            if (i > AOELISTINDEX) {
                break;
            }
            if (AOEBODYS[i] != nullptr) {
                if (AOEBODYS[i]->GetEnableGravity()) {
                    AOEBODYS[i] == nullptr;
                    AOELISTINDEX = AOELISTINDEX - 1;
                }
                else {
                    AOEBODYS[i]->AddForce((AOE_Gravity_Dir * (AOEBODYS[i]->GetMass() * float(tickinterval))), ForceMode::Force);
                }
            }
        }
    }

    Vector3 TempDir;
    if (CurrentType == 'P') {
        for (int i = 0; i < 999; i++) {
            if (i > AOELISTINDEX) {
                break;
            }
            if (AOEBODYS[i] != nullptr) {
                if (AOEBODYS[i]->GetEnableGravity()) {
                    AOEBODYS[i] == nullptr;
                    AOELISTINDEX = AOELISTINDEX - 1;
                }
                else {
                    if (AttratorPoint == ZeroTolerance || AOEBODYS[i]->GetPosition() == AttratorPoint) {
                        break;
                    }
                    TempDir = AOEBODYS[i]->GetPosition() - AttratorPoint;

                    TempDir.Normalize();
                    TempDir = TempDir * (GravityScale * GravityscaleMod) *-1.0f;
                    AOEBODYS[i]->AddForce((TempDir * (AOEBODYS[i]->GetMass() * float(tickinterval))), ForceMode::Force);
                }
            }
        }
    }


    return;
}

bool FakeGravityTest::NewGravityDir(Float3 dir, char type) {
    if (type == 'A') {
        AOE_Gravity_Dir = dir * 981.f;
        return true;
    }
    if(type == 'P') {
        AttratorPoint = dir;
        return true;
    }
    
    return false;
}
//