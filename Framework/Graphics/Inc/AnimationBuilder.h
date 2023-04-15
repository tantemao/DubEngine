#pragma once
#pragma
#include "Animation.h"
namespace DubEngine::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& AddPositionKey(const DEMath::Vector3& position, float time, EaseType easeType = EaseType::Linear);
		AnimationBuilder& AddRoatationKey(const DEMath::Quaternion& rotation, float time, EaseType easeType = EaseType::Linear);
		AnimationBuilder& AddScaleKey(const DEMath::Vector3& scale, float time, EaseType easeType = EaseType::Linear);
		[[nodiscard]] Animation Build();
	private:
		Animation mWorkingCopy;
	};
}