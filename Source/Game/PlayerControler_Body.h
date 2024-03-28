﻿#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Core/Log.h"
#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Engine/Time.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Actor.h"
#include "Engine/Core/Types/Variant.h"
#include "Engine/Core/Math/Matrix.h"

API_CLASS() class GAME_API PlayerControler_Body : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerControler_Body);


API_FIELD() ScriptingObjectReference<RigidBody> PlayerRigidBody = nullptr;
API_FIELD() Vector3 PlayerBodyOfset = (0.0f, 10.0f, 0.0f);
API_FIELD() ScriptingObjectReference<Actor> CamraPiv = nullptr;
API_FIELD() ScriptingObjectReference<Actor> SubPiv = nullptr;

API_FIELD() float MouseSenes = 0.5f;


//Actor* PivCamraPiv;

Transform CurrentTras;
Float2 MousePoDelta;

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;


};