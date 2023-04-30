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

void AnimationUtil::ComputeBoneTransform(ModelId modelId, Bonetransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(modelId);
	if (model->skeleton!=nullptr)
	{
		boneTransforms.resize(model->skeleton->bones.size(), DEMath::Matrix4::Identity);
		ConputeBoneTransformRecursive(model->skeleton->root, boneTransforms);
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