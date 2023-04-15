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

AnimationBuilder& AnimationBuilder::AddPositionKey(const DEMath::vector3& position, float time, EaseType easetype)
{

}