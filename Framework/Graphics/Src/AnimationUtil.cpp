#include"Precompiled.h"
#include"AnimationUtil.h"
#include"Colors.h"
#include"SimpleDraw.h"
#include"Animator.h"
using namespace DubEngine;
using namespace DubEngine::Graphics;
using namespace DubEngine::Graphics::AnimationUtil;

namespace
{
	void ConputeBoneTransformRecursive(const Bone* bone, Bonetransforms& boneTransforms,const Animator* animator)
	{
		if (bone != nullptr)
		{
			if (animator != nullptr)
			{
				boneTransforms[bone->index] = animator->GetToParentTransform(bone);
			}
			else 
			{
				boneTransforms[bone->index] = bone->toParentTransform;

			}
			if (bone->parent != nullptr)
			{
				boneTransforms[bone->index] = animator->GetToParentTransform(bone) * boneTransforms[bone->parentIndex];
			}
			for (auto child : bone->children)
			{
				ConputeBoneTransformRecursive(child, boneTransforms,animator);
			}
		}
	}
}

void AnimationUtil::ComputeBoneTransform(ModelId modelId, Bonetransforms& boneTransforms, const Animator* animator)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton!=nullptr)
	{
		boneTransforms.resize(model->skeleton->bones.size(), DEMath::Matrix4::Identity);
		ConputeBoneTransformRecursive(model->skeleton->root, boneTransforms,animator);
	}
}
void AnimationUtil::ApplyBoneOffsets(ModelId modelId, Bonetransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton != nullptr)
	{
		for (auto& bone : model->skeleton->bones)
		{
			if (bone->parent != nullptr)
			{
				boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
			}
		}
	}

}
void AnimationUtil::DrawSkeleton(ModelId modelId, const Bonetransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton != nullptr)
	{
		for (auto& bone : model->skeleton->bones)
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