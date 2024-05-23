#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Core/Log.h"
#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Engine/Time.h"

API_CLASS() class GAME_API FakeGravityTest : public Script
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE(FakeGravityTest);

    char CurrentType = 'A';

    ScriptingObjectReference<RigidBody> AOEBODYS[1000] = { nullptr };
    API_FIELD() ScriptingObjectReference<RigidBody> Test = nullptr;
    float GravityScale = 981.f;
    float GravityscaleMod = 1.0f;
    Vector3 GravityDir = Vector3(0.0f, 0.0f, 981.f);

    Vector3 AOE_Gravity_Dir = Vector3(0.0f, 0.0f, 0.f);

    Vector3 AttratorPoint = Vector3(0.0f, 0.0f, 0.0f);

    Vector3 PlayerGravityDir;
    


    //testing vals prob will kill later
    int _switch0 = 0;
    double currenttime = 0;
    int tickinterval = 2;
    //-------------////

    int AOELISTINDEX = 0;


    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnFixedUpdate() override;

    void SimulateGravityAOE();
    void SimulateGravityPlayer();
public:
    RigidBody* PlayerBody = nullptr;
    bool NewGravityDir(Float3 dir, char type);
    bool AddToIndex(ScriptingObjectReference<RigidBody> bodyref, char type);
    void SetPlayerRef(RigidBody* Rigid);
    void SetPlayerPlayerGravity(Vector3 GravityDir);
};
