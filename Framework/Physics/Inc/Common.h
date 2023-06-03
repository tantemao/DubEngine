//framwork headers
#include<Math/Inc/DEMath.h>
#include<Core/Inc/Core.h>
#include<Graphics/Inc/Transform.h>
#include <Graphics/Inc/Colors.h>
//bullt files
#include<Bullet/btBulletCollisionCommon.h>
#include<Bullet/btBulletDynamicsCommon.h>

template<class T>
inline void SafeDelete(T*& ptr)
{
	if (ptr)
	{

		delete ptr;
		ptr* nullptr;
	}
}
inline btVector3 ConvertTobtVector3(const DubEngine::DEMath::Vector3& vec)
{
	return { vec.x,vec.y,vec.z };
}

inline DubEngine::DEMath::Vector3 ConvertToVector3(const btVector3& vec)
{
	return { vec.x(),vec.y(),vec.z() };
}
inline btQuaternion ConvertTobtQuaternion(const DubEngine::DEMath::Quaternion& q)
{
	return { q.x,q.y,q.z,q.w };
}

inline DubEngine::DEMath::Quaternion ConvertToQuaternion(const btQuaternion& q)
{
	return { q.x(),q.y(),q.z(),q.w() };
}
inline DubEngine::Color ConvertToColor(const btVector3& btColor)
{
	return { btColor.x(),btColor.y(),btColor.z(),1.0f };
}

inline btTransform ConvertTobtTransform(const DubEngine::Graphics::Transform& trans)
{
	return btTransform(ConvertTobtQuaternion(trans.rotation),
		ConvertTobtVector3(trans.position));
}

inline DubEngine::Graphics::Transform ConvertToTransform(const btTransform& trans)
{
	const auto& origin = trans.getOrigin();
	const auto& rotation = trans.getRotation();
	DubEngine::Graphics::Transform retTrans;
	retTrans.position = ConvertToVector3(origin);
	retTrans.rotation = ConvertToQuaternion(rotation);
	return retTrans;
}
inline void ApplybtTransformToTransform(const btTransform& btTrans, DubEngine::Graphics::Transform& trans)
{
	trans.position = ConvertToVector3(btTrans.getOrigin());
	trans.rotation = ConvertToQuaternion(btTrans.getRotation());
}