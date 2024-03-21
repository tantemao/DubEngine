#pragma once

namespace DubEngine::Physics
{
	class CollisionShape
	{
	public:
		CollisionShape() = default;
		virtual ~CollisionShape();

		virtual void Terminate();
	protected:
		btCollisionShape* mCollisionShape = nullptr;
	private:
		friend class RigidBody;
		btCollisionShape* GetCollisionShape() const { return mCollisionShape; }
	};

	class CollisionShapeSphere :public CollisionShape
	{
	public:
		CollisionShapeSphere() = default;
		void Initialize(float radius);
	};

	class CollisionShapeBox :public CollisionShape
	{
	public:
		CollisionShapeBox() = default;
		void Initialize(const DubEngine::DEMath::Vector3& halfExtents);
	};

	class CollisionShapeEmpty :public CollisionShape
	{
	public:
		CollisionShapeEmpty() = default;
		void Initialize();
	};
}