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
#include "FPSCameraComponent.h"
#include "ModelComponent.h"
#include "MeshComponent.h"
//services
#include "Service.h"
#include "CameraService.h"
#include "UpdateService.h"
#include "RenderService.h"
namespace DubEngine
{
    App& MainApp();
}