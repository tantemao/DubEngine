#pragma once
#include"BlockAllocator.h"
namespace DubEngine::Core
{
	template<class DataType>
	class TypedAllocator :private BlockAllocator
	{
	public:
		TypedAllocator(const char* name, size_t capacity)
			:BlockAllocator(name, sizeof(DataType), capacity)
		{

		}


		template<class... Args>
		DataType* New(Args&&...args)
		{
			auto* instance = static_cast<DataType*>(Allocate());
			new(instance) DataType(std::forward<Args>(args)...);

			return instance;
		}
		void Delete(DataType* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}

			ptr->~DataType();
			Free(ptr);
		}

	};
}