#pragma once


#include"Common.h"
namespace DubEngine
{
	enum class ComponentId
	{
		Invalid,
		Transform,
		Camera,
		FPSCamera,
		Model,

		Count
	};

	enum class ServiceId
	{
		Invalid,
		Camera,
		Update,
		Render,

		Count
	};
	/*enum class NewComponentId
	{
		newId0=
	};*/
}


#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId(){return static_cast<uint32_t>(id);}\
    uint32_t GetTypeId() const override{return StaticGetTypeId();}