#pragma once

#include "Common.h"
#include "App.h"
#include "AppState.h"
#include "GameObject.h"
#include "TypeIds.h"
#include "GameWorld.h"
#include "GameObjectHandle.h"
#include "GameObjectFactory.h"
//component
#include "Component.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
//services
#include "Service.h"
#include "CameraService.h"

namespace DubEngine
{
    App& MainApp();
}