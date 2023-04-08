#include "Precompiled.h"
#include "../Inc/Quaternion.h"
#include "Math/Inc/DEMath.h"

/****************************************************************************
 *
 * Quaternion
 *
 ****************************************************************************/

 //------------------------------------------------------------------------------
 // Comparision operators
 //------------------------------------------------------------------------------

namespace DubEngine::DEMath
{
    //------------------------------------------------------------------------------
    // Quaternion operations
    //------------------------------------------------------------------------------

    inline void Quaternion::Conjugate() noexcept
    {
        x = -x;
        y = -y;
        z = -z;
    }

    inline void Quaternion::Conjugate(Quaternion& result) const noexcept
    {
        result.Conjugate();
    }

    inline void Quaternion::Inverse(Quaternion& result) const noexcept
    {
        float magnitude = result.Magnitude(result);
        result.Conjugate();
        result = result / (magnitude * magnitude);


    }

    inline float Quaternion::Dot(const Quaternion& q) const noexcept
    {
        return w * q.w + x * q.x + y * q.y + z * q.z;
    }

    float Quaternion::Magnitude(const Quaternion& q)
    {
        return std::sqrt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));
    }

    Quaternion Quaternion::Normalize(const Quaternion& q)
    {
        return q / Magnitude(q);
    }

    //------------------------------------------------------------------------------
    // Static functions
    //------------------------------------------------------------------------------

    Quaternion Quaternion::CreateFromAxisAngle(const Vector3& axis, float angle) noexcept
    {
        const float c = cos(angle * 0.5f);
        const float s = sin(angle * 0.5f);
        const DEMath::Vector3 a = DEMath::Normalize(axis);
        return Quaternion(a.x * s, a.y * s, a.z * s, c);
    }

    inline Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept
    {
        float cosYaw = cos(yaw * 0.5f);
        float sinYaw = sin(yaw * 0.5f);
        float cosPitch = cos(pitch * 0.5f);
        float sinPitch = sin(pitch * 0.5f);
        float cosRoll = cos(roll * 0.5f);
        float sinRoll = sin(roll * 0.5f);
        Quaternion q;
        q.x = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
        q.y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
        q.z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
        q.w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;

    }

    inline Quaternion Quaternion::CreateFromRotationMatrix(const Matrix4& M) noexcept
    {
        return Quaternion();
    }

    Quaternion Quaternion::Lerp(Quaternion q0, Quaternion q1, float t)
    {
        return q0 * (1.0f - t) + (q1 * t);
    }

    Quaternion Quaternion::Slerp(Quaternion q1, Quaternion q2, float t)
    {
        // Find the dot product
        float dot = (q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w);

        // Determine the direction of the rotation.
        //if (dot < 0.0f)
        //{
        //    dot = -dot;
        //    q2.x = -q2.x;
        //    q2.y = -q2.y;
        //    q2.z = -q2.z;
        //    q2.w = -q2.w;
        //}
        if (dot > 0.999f)
        {
            return Normalize(Lerp(q1, q2, t));
        }

        float theta = acosf(dot);
        float sintheta = sinf(theta);
        float scale0 = sinf(theta * (1.0f - t)) / sintheta;
        float scale1 = sinf(theta * t) / sintheta;

        // Perform the slerp
        return Quaternion
        (
            (q1.x * scale0) + (q2.x * scale1),
            (q1.y * scale0) + (q2.y * scale1),
            (q1.z * scale0) + (q2.z * scale1),
            (q1.w * scale0) + (q2.w * scale1)
        );
    }
}