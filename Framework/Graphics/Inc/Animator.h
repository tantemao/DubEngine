#pragma once


#include"ModelManager.h"
#include"Bone.h"
namespace DubEngine::Graphics
{
	class Animator
	{
	public:
		void Initialize(ModelId id);
		void PlayAnimation(int clipIndex, bool looping);
		void Update(float deltaTime);
		bool IsFinished();

		size_t GetAnimationCount() const;
		DEMath::Matrix4 GetToParentTransform(const Bone* bone) const;

	private:
		ModelId mModelId = 0;
		int mClipIndex = 0;
		bool mLooping = false;
		float mAnimationTrack = 0.0f;
	};
}