#pragma once
#include "Bone.h"
namespace DubEngine::Graphics
{

	struct Skeleton
	{
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};
}