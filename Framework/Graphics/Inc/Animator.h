#pragma once


#include"ModelManager.h"
#include"Bone.h"
namespace DubEngine::Graphics
{

	class BlendNode
	{
	public:


		BlendNode() = default;
		//delete copies
		BlendNode(BlendNode&) = delete;
		BlendNode& operator=(BlendNode&) = delete;
		//override moves
		BlendNode(BlendNode && rhs)noexcept;
		BlendNode& operator=(BlendNode && rhs)noexcept;


		void PlayAnimation(ModelId id, int clipIndex, bool looping);
		void Update(float deltaTime);
		bool GetToParentTransform(const Bone* bone,Transform& transform) const;

		bool IsFinished() const;
		float GetAnimationTick()const { return mAnimationTick; }
		bool IsLooping() const { return mLooping; }
		int GetClipIndex() const { return mClipIndex; };

		
		
	private:
		ModelId mModelId = 0;
		int mClipIndex = -1;
		float mAnimationTick = 0.0f;
		bool mLooping = false;

	};
	class Animator
	{
	public:
		void Initialize(ModelId id);
		void PlayAnimation(int clipIndex, bool looping,float blendDuration=0.0f);
		void Update(float deltaTime);
		bool IsFinished();

		size_t GetAnimationCount() const;
		DEMath::Matrix4 GetToParentTransform(const Bone* bone) const;

	private:
		ModelId mModelId = 0;
		float mBlendDuration = -1;
		float mBlendTime = -1.0f;

		BlendNode mCurrentAnimation;
		BlendNode mNextAnimation;

		//BlendNode mAnimation[8];
		//blend walkfwd & runfwd by 50%
	};
}