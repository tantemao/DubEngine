#include"Precompiled.h"
#include"PhysicsWorld.h"
#include"PhysicsDebugDrawer.h"
#include"RigidBody.h"
using namespace DubEngine;
using namespace DubEngine::Physics;
namespace
{
	std::unique_ptr<PhysicsWorld> sPhysicsWorld;
}
void PhysicsWorld::StaticIntialize(const Settings& settings)
{
	ASSERT(sPhysicsWorld == nullptr, "PhysicsWorld: is already initialized");
	sPhysicsWorld = std::make_unique<PhysicsWorld>();
	sPhysicsWorld->Intialize(settings);
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
	for (auto& rb : mRigidBodies)
	{
		rb->UpdateTransform();
	}

}
void PhysicsWorld::DebugUI()
{
	ImGui::Checkbox("RenderPhysics##", &mRenderDebugUI);
	if (mRenderDebugUI)
	{
		int debugMode = mDebugDrawer->getDebugMode();
		bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe) > 0;
		if (ImGui::Checkbox("[DBG]DrawWireFrame##", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawWireframe : debugMode & ~btIDebugDraw::DBG_DrawWireframe;
		}
		isEnabled = (debugMode & btIDebugDraw::DBG_DrawAabb) > 0;
		if (ImGui::Checkbox("[DBG]DrawAabb##", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawAabb : debugMode & ~btIDebugDraw::DBG_DrawAabb;
		}
		mDebugDrawer->setDebugMode(debugMode);
		mDynamicWorld->debugDrawWorld();
	}

}

void PhysicsWorld::Register(RigidBody* rigidBody)
{
	if (rigidBody != nullptr)
	{
		mRigidBodies.push_back(rigidBody);
		if (rigidBody->GetRigidBody() != nullptr)
		{
			mDynamicWorld->addRigidBody(rigidBody->GetRigidBody());
		}
	}

}
void PhysicsWorld::Unregister(RigidBody* rigidBody)
{
	if (rigidBody != nullptr)
	{
		auto iter = std::find(mRigidBodies.begin(), mRigidBodies.end(), rigidBody);
		if (iter != mRigidBodies.end())
		{
			if (rigidBody->GetRigidBody() != nullptr)
			{
				mDynamicWorld->removeRigidBody(rigidBody->GetRigidBody());
			}
			mRigidBodies.erase(iter);
		}
	}
}