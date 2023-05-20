#pragma once
#include "Skeleton.h"
#include"ModelManager.h"
#include"Animator.h"
namespace DubEngine::Graphics::AnimationUtil
{
	using Bonetransforms = std::vector<DEMath::Matrix4>;

	void ComputeBoneTransform(ModelId modelId, Bonetransforms& boneTransforms, const Animator* animator = nullptr);
	void ApplyBoneOffsets(ModelId modelId, Bonetransforms& boneTransforms);
	void DrawSkeleton(ModelId modelId, const Bonetransforms& boneTransforms);
}