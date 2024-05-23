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
#include "ThirdPersonPlayerContoller.h"

API_CLASS() class GAME_API PlayerCamManger : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(PlayerCamManger);


    bool follow_player = true;
    ThirdPersonPlayerContoller* PlayerController = nullptr;
    //

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

public:
    bool laggycam = false;
};
