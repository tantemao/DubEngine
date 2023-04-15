#pragma once
#include "Common.h"
namespace DubEngine::Graphics
{

	enum EaseType
	{
		Linear,
		EaseIn,
		EaseOut,
		EaseInput,
		EaseInQuad,
		EaseOutQuad,
		EaseInOutQuad
	};
	template<class T>
	struct KeyFrame
	{
		KeyFrame() = default;
		KeyFrame(const T& k,float t,EaseType e)
			:key(k)
			,time(t)
			,easetype(e)
		{
		
		
		}

		T key = T();
		float time = 0.0f;
		EaseType easetype = EaseType::Linear;
	};


	template<class T>
	using Keyframes = std::vector<KeyFrame<T>>;
	using PositionKeys = Keyframes<DEMath::Vector3>;
	using RotationKeys = Keyframes<DEMath::Quaternion>;
	using ScaleKeys = Keyframes<DEMath::Vector3>;





}