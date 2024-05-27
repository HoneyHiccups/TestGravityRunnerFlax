#pragma once

#include "Engine/Physics/Actors/RigidBody.h"
#include "Engine/Core/Log.h"
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

    // bais and core can not be same
    //use with normlized vectors

    // takes a new plane and shifts the forward vector to be Perpendicular to the new plane
    static inline Vector3 VectorPlaneShift(Vector3 PlaneToOrientTo, Vector3 CurrentLeftVector); //returns a new forward vector that is Perpendicular to inputed plane
};

struct SudoPlane {

    Vector3 WorldPostionA;
    Vector3 WorldPostionB;
    Vector3 WorldPostionC;


    Vector3 AB;

    Vector3 CA;
    /*
    SudoPlane(Vector3 a, Vector3 b, Vector3 c)
        : WorldPostionA(a), WorldPostionB(b), WorldPostionC(c) {
        __MakePlane();
    }
    */
    void SetPlaneVectors(Vector3 a, Vector3 b, Vector3 c) {
        WorldPostionA = a;
        WorldPostionB = b;
        WorldPostionC = c;
        __MakePlane();
    }

    // fix this the trianal needs to be equalatarl not right angle


    void __MakePlane() {
        AB = WorldPostionA - WorldPostionB;
        CA = WorldPostionC - WorldPostionA;
        AB.Normalize();
        CA.Normalize();
    }
    
    Float3 GetUp() {
        Vector3 output = Vector3::Cross(AB, CA); \
        output.Normalize();
        return output;
    }

    Float3 GetDown() {
        return GetUp() * -1.0f;
    }

    Vector3 ProjectToPlane(Vector3 vector) { // needs testing
        return Vector3::ProjectOnPlane(vector, this->AB - this->CA);
    }
};