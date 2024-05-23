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
#include "FakeGravityTest.h"
#include "Maths.h"

API_CLASS() class GAME_API ThirdPersonPlayerContoller : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(ThirdPersonPlayerContoller);

ScriptingObjectReference<Camera> PlayerCam = nullptr;
API_FIELD() ScriptingObjectReference<RigidBody> RigidBody;
API_FIELD() ScriptingObjectReference<Actor> BodyHolder;
API_FIELD() ScriptingObjectReference<Actor> CamRig;

API_FIELD() ScriptingObjectReference<Actor> PlayerLookAtBall;
API_FIELD() ScriptingObjectReference<Actor> LookAtCube;
API_FIELD() ScriptingObjectReference<Actor> PlayerFace;
API_FIELD() ScriptingObjectReference<Actor> EndPoint;
API_FIELD() float MaxTorq = 5000.0f;
API_FIELD() float Jumpz = 10000.0f;

float lookSens = 0.3f;

RayCastHit SpringArmHitR;

Vector2 Input;
Vector2 InputDir = 0.0f;
Vector3 WishDir;

Vector3 GravityDir = Vector3(0.0f, -1.0f, 0.0f);

float BaseLinearDamping;

//buttons
bool LevButton; bool UnlevButton; bool jumpbuttun;
uint8_t LevState = 0; //0 Normal // 1 Leving // 2 AugFalling

// [Script]
void OnEnable() override;
void OnDisable() override;
void OnUpdate() override;
void InputStack();
void CameraAttached(Camera* cam);
void OnFixedUpdate() override;
Vector3 Forceinverston(Vector3& v);
void Jump();
void TwistToGravity(Vector3 gv);
void Levitate();
void AugFalling(Vector3 pickdir);
void UnLevitate();
void IsPlayerGrounded();
Float3 GetFaceNormal();
void lindampingMod();
void JustLanded();

public:
    Vector3 CamTargetLoc;
    API_FIELD() ScriptingObjectReference<Actor> HPiv;
    API_FIELD() ScriptingObjectReference<Actor> VPiv;
    

private:
    
    bool b_body_orient_gravity = false; //depracate soon
    ScriptingObjectReference<FakeGravityTest> GravityManger = nullptr;
    Quaternion BodyAimOrent;
    RayCastHit SurfaceGripper;
    RayCastHit IsGroundedSweep;
    bool bgrounded = false;
    float targetdamping;
    float bodytwistspeed = 7.f;

private:
    double timmerticks[2] = { 0.0, .07 };
    /*using this as a way for fufnctions to keep track of the delta times for
    non expotal lerps, and true lin*/
    // 0 is for linddaming mod
    // 1 is used as a cd timmer for jump

protected:
    bool justlanded = false; // not to be read.
    bool openrezjumpcd = false;
public:
    bool bcanjump = false;
};
