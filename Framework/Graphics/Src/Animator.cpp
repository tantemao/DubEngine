#include"Precompiled.h"
#include"Animator.h"


using namespace DubEngine;
using namespace DubEngine::Graphics;
void Animator::Initialize(ModelId id)
{
	mModelId = id;
}

void Animator::PlayAnimation(int clipIndex, bool looping)
{
	mClipIndex = clipIndex;
	mAnimationTrack = 0.0f;
	mLooping = looping;

}

void Animator::Update(float deltaTime)
{
	auto model = ModelManager::Get()->GetModel(mModelId); 
	const auto& animClip = model->animationClips[mClipIndex]; 
	mAnimationTrack += deltaTime*animClip.ticksPerSecond; 
	if (mAnimationTrack > animClip.tickDuration)
	{
		if (mLooping && animClip.tickDuration > 0.0f)
		{
			while (mAnimationTrack > animClip.tickDuration)
			{
				mAnimationTrack -= animClip.tickDuration;

			}
		}
		else
		{
			mAnimationTrack = animClip.tickDuration;
		}
	}
}

bool Animator::IsFinished()
{
	if (mLooping)
	{
		return false;
	}
	auto model = ModelManager::Get()->GetModel(mModelId); 
	const auto& animClip = model->animationClips[mClipIndex]; 
	return mAnimationTrack >= animClip.tickDuration;
}

size_t Animator::GetAnimationCount() const
{
	auto model = ModelManager::Get()->GetModel(mModelId); 
	return model->animationClips.size();
}

DEMath::Matrix4 Animator::GetToParentTransform(const Bone* bone) const
{
	auto model = ModelManager::Get()->GetModel(mModelId); 
	const auto& animClip = model->animationClips[mClipIndex]; 
	auto& animation = animClip.boneAnimations[bone->index]; 
	if (animation == nullptr)
	{
		return bone->toParentTransform;
	}
	return animation->GetTransform(mAnimationTrack).GetMatrix4();
}
