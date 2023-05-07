#pragma once
#include "KeyFrame.h"
#include"Transform.h"
namespace DubEngine::Graphics
{

	class Animation
	{
	public:
		DEMath::Vector3 GetPosition(float time) const;
		DEMath::Quaternion GetRoatation(float time) const;
		DEMath::Vector3 GetScale(float time) const;

		Transform GetTransform(float time) const;

		float GetDuration()const;
	private:
		friend class AnimationBuilder;
		friend class AnimationIO;

		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;
		float mDuration;
	};

}