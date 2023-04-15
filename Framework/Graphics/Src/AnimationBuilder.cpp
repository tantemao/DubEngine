#include "Precompiled.h"
#include "AnimationBuilder.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::DEMath;
namespace {
	template<class T>
	inline void PushKey(Keyframes<T>& keyframes, const T& value, float time,EaseType easeType)
	{
		
		ASSERT(keyframes.empty() || keyframes.back().time < time, "AnimationBuilder--Cannot add keyframe back in time");
		keyframes.emplace_back(value, time,easeType);

	}

}



AnimationBuilder& AnimationBuilder::AddPositionKey(const DEMath::Vector3& position, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mPositionKeys, position, time,easeType);
	mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
	return*this;
}



AnimationBuilder& AnimationBuilder::AddRoatationKey(const DEMath::Quaternion& rotation, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mRotationKeys, rotation, time,easeType);
	mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
	return*this;
}
AnimationBuilder& AnimationBuilder::AddScaleKey(const DEMath::Vector3& scale, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mPositionKeys, scale, time,easeType);
	mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
	return*this;
}
