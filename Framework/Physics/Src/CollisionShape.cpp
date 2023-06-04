#include"Precompiled.h"
#include"CollisionShape.h"

using namespace DubEngine;
using namespace DubEngine::Physics;
CollisionShape::~CollisionShape()
{
	ASSERT(mCollisionShape == nullptr, "CollisionShape: terminate must be called first");

}

void CollisionShape::Terminate()
{
	SafeDelete(mCollisionShape);
}

void CollisionShapeSphere::Initialize(float radius)
{
	ASSERT(mCollisionShape == nullptr, "CollisionShapeSphere:collision shape has already been created");
	mCollisionShape = new btSphereShape(radius);
}
void CollisionShapeBox::Initialize(const DubEngine::DEMath::Vector3& halfExtents)
{
	ASSERT(mCollisionShape == nullptr, "CollisionShapebOX:collision shape has already been created");
	mCollisionShape = new btBoxShape(ConvertTobtVector3(halfExtents));
}