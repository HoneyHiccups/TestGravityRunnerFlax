#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Core/Log.h"
#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Engine/Time.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Actor.h"
#include "Engine/Level/SceneObject.h"
#include "Engine/Level/Scene/Scene.h"
#include "Engine/Physics/Colliders/Collider.h"
#include "Engine/Physics/Colliders/SphereCollider.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Scripting/Types.h"
#include "Engine/Scripting/ScriptingType.h"
#include "Engine/Scripting/ScriptingObject.h"
#include "FakeGravityTest.h" // my script

API_CLASS() class GAME_API GravityGun : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(GravityGun);

   API_FIELD() float CastDist = 600.0f;
   API_FIELD() float grab_strength = 1500.0f;

   char CastingType = 'A';
   FakeGravityTest* GravityMangerptr; //actor owner of my script
   Script* GravityManger = nullptr; // script ptr
   RayCastHit Hit;
   RayCastHit AltHit;
   RigidBody* BodyPtr = nullptr;
   Vector3 GravityPullLoc =(0.f, 0.f, 0.f);


    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    //void OnFixedUpdate() override;


    bool PickObject();
    void PickGravityEndPoint();
    void MakeVectors();


};
