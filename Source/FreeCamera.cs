using FlaxEngine;

public class FreeCamera : Script
{
    [Limit(0, 100), Tooltip("Camera movement speed factor")]
    public float MoveSpeed { get; set; } = 4;

    [Tooltip("Camera rotation smoothing factor")]
    public float CameraSmoothing { get; set; } = 20.0f;

    private float pitch;
    private float yaw;
    public Transform tras;

    public override void OnStart()
    {
        var initialEulerAngles = Actor.Orientation.EulerAngles;
        pitch = initialEulerAngles.X;
        yaw = initialEulerAngles.Y;
    }

    public override void OnUpdate()
    {
        var camTrans = Actor.Transform;
        Screen.CursorVisible = false;
        Screen.CursorLock = CursorLockMode.Locked;

        var mouseDelta = new Float2(Input.GetAxis("Mouse X"), Input.GetAxis("Mouse Y")) *.5;
        pitch = Mathf.Clamp(pitch + mouseDelta.Y, -88, 88);
        yaw += mouseDelta.X;
        camTrans.Orientation = Quaternion.Euler(pitch, yaw, 0);
        tras = camTrans;

    }

    public override void OnFixedUpdate()
    {

        //var camTrans = tras;
        var camFactor = Mathf.Saturate(CameraSmoothing * Time.DeltaTime);

        //camTrans.Orientation = Quaternion.Lerp(camTrans.Orientation, Quaternion.Euler(pitch, yaw, 0), camFactor);
        


        var inputH = Input.GetAxis("Horizontal");
        var inputV = Input.GetAxis("Vertical");
        var move = new Vector3(inputH, 0.0f, inputV);
        move.Normalize();
        move = tras.TransformDirection(move);

        tras.Translation += move * MoveSpeed;

        Actor.Transform = tras;
    }
}
