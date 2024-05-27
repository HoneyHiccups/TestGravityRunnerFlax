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
//#include "Engine/Core/Math/Vector3.h"


API_CLASS() class GAME_API PlayerControler_Body : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerControler_Body);


API_FIELD() ScriptingObjectReference<RigidBody> PlayerRigidBody = nullptr;

API_FIELD() ScriptingObjectReference<Actor> CamraPiv = nullptr;
API_FIELD() ScriptingObjectReference<Actor> SubPiv = nullptr;
API_FIELD() ScriptingObjectReference<Actor> PlayerMeshHolder = nullptr;

ScriptingObjectReference<Camera> PlayerCamera = nullptr;
ScriptingObjectReference<Actor> CamreaTargetPoint = nullptr;
ScriptingObjectReference<Actor> CamLookAtVector_Start = nullptr;
ScriptingObjectReference<Script> GravityManger = nullptr;
//Script* GravityManger = nullptr;
API_FIELD() float MouseSenes = 0.5f;
API_FIELD() float SpringArmSmoothing = 30.0f;
API_FIELD() int MaxJumps = 1;
API_FIELD() float JumpHeight= 3500.0f; 

//Actor* PivCamraPiv;

Transform CurrentTras;
Float2 MousePoDelta;
Vector3 ForwardVec;
Vector3 UpVec;
Vector3 RightVec;
Vector3 WishDir;
Vector3 LookAtLoc;


Float3 GravityDir = Float3(0.0f,-1.0f,0.0f);
RayCastHit GroundCheckHit;

float BaseAngleDamp;

RayCastHit SpringArmHit;
float PlayerBodyOfset = 60.4f;
float MaxFollowCamDist = -471.f;
float MinFollowDist = 50.0f;
bool OnGround;
int CurrentJumps;
//Vector3 targetloc;

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void JustLanded();

    void NullGravity();


};
