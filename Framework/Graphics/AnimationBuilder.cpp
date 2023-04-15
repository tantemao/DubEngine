#include "Precompiled.h"
#include "AnimationBuilder.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::DEMath;
namespace
{
	template<class T>
	inline void PushKey(KeyFrames<T>& keyframes, constT& value, float time)
	{
		ASSERT(keyframes.empty() || keyframes.back().time < time, "AnimationBuilder--Cannot add keyframe back in time");
		keyframes.emplace_back(value, time);

	}
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const DEMath::Vector3& position, float time, EaseType easeType)
{
	PushKey(mWorkingCopy mPositionKeys, position, time);
	mWorkingCopy mDuration = Max(mWorkingCopy mDuration, time);
	return*this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const DEMath::Quaternion& rotation, float time, EaseType easeType)
{
	PushKey(mWorkingCopy mRotationKeys, position, time);
	mWorkingCopy mDuration = Max(mWorkingCopy mDuration, time);
	return*this;
}
AnimationBuilder& AnimationBuilder::AddScaleKey(const DEMath::Vector3& scale, float time, EaseType easeType)
{
	PushKey(mWorkingCopy mPositionKeys, scale, time);
	mWorkingCopy mDuration = Max(mWorkingCopy mDuration, time);
	return*this;
}