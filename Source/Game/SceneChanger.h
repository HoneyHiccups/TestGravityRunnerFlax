#pragma once

#include "Engine/Scripting/Script.h"
#include "Engine/Content/SceneReference.h"
#include "Engine/Input/Input.h"
#include "Engine/Level/Level.h"

API_CLASS() class GAME_API SceneChanger : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(SceneChanger);

API_FIELD() SceneReference Scene;

    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
};
