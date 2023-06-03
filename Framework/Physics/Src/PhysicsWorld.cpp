#include"Precompiled.h"
#include"PhysicsWorld.h"
#include"PhysicsDebugDrawer.h"
using namespace DubEngine;
using namespace DubEngine::Physics;
namespace
{
	std::unique_ptr<PhysicsWorld> sPhysicsWorld;
}
void PhysicsWorld::StaticIntialize(const Settings& settings)
{
	ASSERT(sPhysicsWorld == nullptr, "PhysicsWorld: is already initialized");
}
void PhysicsWorld::StaticTerminate()
{
	if (sPhysicsWorld != nullptr)
	{
		sPhysicsWorld->Terminate();
		sPhysicsWorld.reset();
	}

}
PhysicsWorld* PhysicsWorld::Get()
{
	ASSERT(sPhysicsWorld != nullptr, "PhysicsWorld: is not intialized");
	return sPhysicsWorld.get();
}
PhysicsWorld::~PhysicsWorld()
{
	ASSERT(mDynamicWorld == nullptr, "PhysicsWorld: terminate must be called before deletion");

}
void PhysicsWorld::Intialize(const Settings& settings)
{
	mSettings = settings;
	mCollisionConfiguration = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
	mInterface = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver();
	mDynamicWorld = new btDiscreteDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguration);
	mDynamicWorld->setGravity(ConvertTobtVector3(settings.gravity));

	mDebugDrawer = new PhysicsDebugDrawer();
	mDynamicWorld->setDebugDrawer(mDebugDrawer);
}
void PhysicsWorld::Terminate()
{
	SafeDelete(mDynamicWorld);
	SafeDelete(mSolver);
	SafeDelete(mInterface);
	SafeDelete(mDispatcher);
	SafeDelete(mCollisionConfiguration);
}
void PhysicsWorld::Update(float deltaTime)
{
	mDynamicWorld->stepSimulation(deltaTime, mSettings.simulationSteps, mSettings.fixedTimeStep);

}
void PhysicsWorld::DebugUI()
{
	if (mRenderDebugUI)
	{
		mDynamicWorld->debugDrawWorld();
	}

}