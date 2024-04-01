#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Core/Log.h"
#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Engine/Time.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Actor.h"
#include "Engine/Core/Types/Variant.h"
#include "Engine/Core/Math/Matrix.h"

API_CLASS() class GAME_API RigidBodyTestingScript : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(RigidBodyTestingScript);

API_FIELD() ScriptingObjectReference<RigidBody> testingbody = nullptr;
API_FIELD() Vector3 Force = Vector3(0.0f, 0.0f, 0.0f);
float elaspedtime = 1.0f;

bool opengate[100] = { false };
    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
};
