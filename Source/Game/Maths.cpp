#include "Maths.h"
#include "Engine/Core/Log.h"

void Maths::RunNativeAction(Vector4 data)
{
    LOG(Warning, "Data in RunNativeAction: {0}", data);
}

Vector3 Maths::SnappVector(Float3 v) {
    Float3 tosnap[4];

    return Vector3(0.0f, 0.0f, 0.0f);
}


Vector3 Maths::VectorPlaneShift(Vector3 PlaneToOrientTo, Vector3 CurrentLeftVector) {
    return Vector3::ProjectOnPlane(Vector3::Cross(PlaneToOrientTo, (CurrentLeftVector *-1.0f ) ), CurrentLeftVector);
}