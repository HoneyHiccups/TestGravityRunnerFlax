#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Core/Log.h"
#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Engine/Time.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Actor.h"
#include "Engine/Level/Actors/Camera.h"
#include "Engine/Core/Types/Variant.h"
#include "Engine/Core/Math/Matrix.h"
#include "Engine/Level/Scene/Scene.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Physics/Colliders/Collider.h"
#include "Engine/Engine/Screen.h"


API_CLASS() class GAME_API PlayerPawn : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerPawn);

ScriptingObjectReference<Camera> PlayerCam =nullptr;
API_FIELD() ScriptingObjectReference<RigidBody> RigidBody;
API_FIELD() ScriptingObjectReference<Actor> BodyHolder;
API_FIELD() ScriptingObjectReference<Actor> CamRig;

API_FIELD() ScriptingObjectReference<Actor> EndPoint;
API_FIELD() float MaxMoveSpeed = 5000.0f;

float lookSens = 0.3f;

RayCastHit SpringArmHitR;

Vector2 Input;
Vector2 InputDir = 0.0f;
Vector3 WishDir;

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void CameraAttached(Camera* cam);
    void OnFixedUpdate() override;
    public:
        Vector3 CamTargetLoc;
        API_FIELD() ScriptingObjectReference<Actor> HPiv;
        API_FIELD() ScriptingObjectReference<Actor> VPiv;
};

//