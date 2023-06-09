#include"Precompiled.h"
#include"Animator.h"


using namespace DubEngine;
using namespace DubEngine::Graphics;



BlendNode::BlendNode(BlendNode&& rhs) noexcept
	:mModelId( rhs.mModelId)
	,mClipIndex (rhs.mModelId)
	,mAnimationTick (rhs.mAnimationTick)
	,mLooping (rhs.mLooping)
{
	rhs.mModelId = 0;
	rhs.mClipIndex = -1;
	rhs.mAnimationTick = 0.0f;
	rhs.mLooping = false;
}
BlendNode& BlendNode::operator=(BlendNode&& rhs) noexcept
{
	mModelId = rhs.mModelId;
	mClipIndex = rhs.mClipIndex;
	mAnimationTick = rhs.mAnimationTick;
	mLooping = rhs.mLooping;
	rhs.mModelId = 0;
	rhs.mClipIndex = -1;
	rhs.mAnimationTick = 0.0f;
	rhs.mLooping = false;
	return*this;
}
void BlendNode::PlayAnimation(ModelId id, int clipIndex, bool looping)
{
	mModelId = id;
	mClipIndex = clipIndex;
	mLooping = looping;
	mAnimationTick = 0.0f;
}
void BlendNode::Update(float deltaTime) 
{
	auto model = ModelManager::Get()->GetModel(mModelId);
	const auto& animClip = model->animationClips[mClipIndex];
	mAnimationTick += animClip.ticksPerSecond * deltaTime;
	if (mAnimationTick > animClip.tickDuration)
	{
		if (mLooping)
		{
			while (mAnimationTick >= animClip.tickDuration)
			{
				mAnimationTick -= animClip.tickDuration;
			}
		}
		else
		{
			mAnimationTick = animClip.tickDuration;
		}
	}
}
bool BlendNode::GetToParentTransform(const Bone* bone,Transform& transform) const
{
	auto model = ModelManager::Get()->GetModel(mModelId);
	const auto& animClip = model->animationClips[mClipIndex];
	auto& animation = animClip.boneAnimations[bone->index];
	if (animation == nullptr)
	{
		return false;
	}
	transform= animation->GetTransform(mAnimationTick);
	return true;
}

bool BlendNode::IsFinished() const
{
	if (mLooping||mClipIndex<0)
	{
		return false;
	}
	auto model = ModelManager::Get()->GetModel(mModelId);
	const auto& animClip = model->animationClips[mClipIndex];
	return mAnimationTick >= animClip.tickDuration;
}


void Animator::Initialize(ModelId id)
{
	mModelId = id;
}

void Animator::PlayAnimation(int clipIndex, bool looping,float blendDuration)
{
	if (mCurrentAnimation.GetClipIndex() == -1|| blendDuration<=0.0f)
	{
		mCurrentAnimation.PlayAnimation(mModelId, clipIndex, looping);
		
	}
	else
	{
		mNextAnimation.PlayAnimation(mModelId, clipIndex, looping);
		mBlendDuration = blendDuration;
		mBlendTime = 0.0f;
	}

}

void Animator::Update(float deltaTime)
{
	if (mCurrentAnimation.GetClipIndex() != -1)
	{
		mCurrentAnimation.Update(deltaTime);
	}
	if (mNextAnimation.GetClipIndex() != -1)
	{
		mNextAnimation.Update(deltaTime);
	}
	if (mBlendDuration > 0.0f && mBlendTime < mBlendDuration)
	{
		mBlendTime += deltaTime;
		if (mBlendTime >= mBlendDuration)
		{
			mBlendTime = 0.0f;
			mBlendDuration = 0.0f;
			mCurrentAnimation = std::move(mNextAnimation);
		}
	}
}


bool Animator::IsFinished()
{
	return mCurrentAnimation.IsFinished();
}

size_t Animator::GetAnimationCount() const
{
	auto model = ModelManager::Get()->GetModel(mModelId); 
	return model->animationClips.size();
}

DEMath::Matrix4 Animator::GetToParentTransform(const Bone* bone) const
{
	Transform fromTransform;
	if (! mCurrentAnimation.GetToParentTransform(bone,fromTransform))
	{
		return bone->toParentTransform;
	}
	if (mNextAnimation.GetClipIndex() != -1)
	{
		float t = DEMath::Clamp(mBlendTime / mBlendDuration, 0.0f, 1.0f);
		Transform toTransform;
		if (!mNextAnimation.GetToParentTransform(bone, toTransform))
		{
			return bone->toParentTransform;
		}

		Transform blendTransform;
		blendTransform.position = DEMath::Lerp(fromTransform.position, toTransform.position, t);
		blendTransform.rotation = DEMath::Quaternion::Slerp(fromTransform.rotation, toTransform.rotation, t);
		blendTransform.scale = DEMath::Lerp(fromTransform.scale, toTransform.scale, t);

		return blendTransform.GetMatrix4();
	}
	return fromTransform.GetMatrix4();
}
