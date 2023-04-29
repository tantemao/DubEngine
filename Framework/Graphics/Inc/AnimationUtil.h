#pragma once
#include "Skeleton.h"
namespace DubEngine::Graphics::AnimationUtil
{
	using Bonetransforms = std::vector<DEMath::Matrix4>;

	void ComputeBoneTransform(const Skeleton* skeleton, Bonetransforms& boneTransforms);
	void ApplyBoneOffsets(const Skeleton* skeleton, Bonetransforms& boneTransforms);
	void DrawSkeleton(const Skeleton* skeleton, const Bonetransforms& boneTransforms);
}