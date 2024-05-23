#pragma once

#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Scripting/ScriptingObjectReference.h"
#include "Engine/Engine/Time.h"
#include "Engine/Level/Actor.h"
#include "Engine/Core/Types/Variant.h"
#include "Engine/Core/Math/Matrix.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Physics/Colliders/Collider.h"
#include "Engine/Scripting/Script.h"
#include "Engine/Core/Math/Vector4.h"
#include "Engine/Core/Math/Vector3.h"

/// <summary>
/// Maths Function Library
/// </summary>
API_CLASS(Static) class GAME_API Maths 
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(Maths);
public:

    /// <summary>
    /// Logs the function parameter natively.
    /// </summary>
    /// <param name="data">Data to pass to native code</param>
    API_FUNCTION() static void RunNativeAction(Vector4 data);

    static Vector3 SnappVector(Float3 v);
};
