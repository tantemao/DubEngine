#include "Precompiled.h"
#include"PhysicsDebugDrawer.h"
#include <Graphics/Inc/SimpleDraw.h>
using namespace DubEngine;
using namespace DubEngine::Physics;
using namespace DubEngine::Graphics;

void PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	SimpleDraw::AddLine(ConvertToVector3(from), ConvertToVector3(to), ConvertToColor(color));
}
void PhysicsDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int LifeTime, const btVector3& color)
{
	// nothing here atm
}
void PhysicsDebugDrawer::reportErrorWarning(const char* warningString)
{
	//LOG["[PhysicsWarning] &s", warningString];
}
void PhysicsDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
	//nothing implemented
}
void PhysicsDebugDrawer::setDebugMode(int debugMode)
{
	mDebugMode = debugMode;
}
int PhysicsDebugDrawer::getDebugMode() const
{
	return mDebugMode;
}