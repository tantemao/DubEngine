#include"Precompiled.h"
#include"AnimationUtil.h"
#include"Colors.h"
#include"SimpleDraw.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Graphics::AnimationUtil;

namespace
{
	void ConputeBoneTransformRecursive(const Bone* bone, Bonetransforms& boneTransforms)
	{
		if (bone != nullptr)
		{
			if (bone->parent != nullptr)
			{
				boneTransforms[bone->index] = bone->toParentTransform * boneTransforms[bone->parentIndex];
			}
			else
			{
				boneTransforms[bone->index] = bone->toParentTransform;
			}
			for (auto child : bone->children)
			{
				ConputeBoneTransformRecursive(child, boneTransforms);
			}
		}
	}
}

void AnimationUtil::ComputeBoneTransform(const Skeleton* skeleton, Bonetransforms& boneTransforms)
{
	if (skeleton != nullptr)
	{
		boneTransforms.resize(skeleton->bones.size(), DEMath::Matrix4::Identity);
		ConputeBoneTransformRecursive(skeleton->root, boneTransforms);
	}
}
void AnimationUtil::ApplyBoneOffsets(const Skeleton* skeleton, Bonetransforms& boneTransforms)
{
	if (skeleton != nullptr)
	{
		for (auto& bone : skeleton->bones)
		{
			if (bone->parent != nullptr)
			{
				boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
			}
		}
	}

}
void AnimationUtil::DrawSkeleton(const Skeleton* skeleton, const Bonetransforms& boneTransforms)
{
	if (skeleton != nullptr)
	{
		for (auto& bone : skeleton->bones)
		{
			if (bone->parent != nullptr)
			{
				const auto posA = DEMath::GetTranslation(boneTransforms[bone->index]);
				const auto posB = DEMath::GetTranslation(boneTransforms[bone->parentIndex]);
				SimpleDraw::AddLine(posA, posB, Colors::HotPink);
			}
		}
	}
}