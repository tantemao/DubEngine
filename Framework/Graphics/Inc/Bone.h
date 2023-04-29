#pragma once
#include"Common.h"

namespace DubEngine::Graphics 
{
	struct Bone
	{
	std::string name;
	int index = -1;
	Bone* parent = nullptr;
	int parentIndex = -1;


	std::vector<Bone*> children;
	std::vector <int> childrenIndicies;

	DEMath::Matrix4 toParentTransform;
	DEMath::Matrix4 offsetPartentTransform;


	};

}