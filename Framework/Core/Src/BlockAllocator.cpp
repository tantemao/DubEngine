#include"Precompiled.h"
#include"BlockAllocator"

#include"DebugUtil.h"

using namespace DubEngine;
using namespace DubEngine::Core;

BlockAllocator::BlockAllocator(const char* name, size_t blockSize, size_t capacity)
	:mName(name)
	,mBlockSize(blockSize)
	,mCapacity(capacity)
	,mFreeBlocks(capacity)
{
	ASSERT(blockSize > 0, "BlockAllocator:invalid block size");
	ASSERT(capacity > 0, "BlockAllocator: invalid capacity");
	mData = std::malloc(blockSize * capacity);
	for (size_t i = 0; i < capacity; ++i)
	{
		mFreeBlock[i] = static_cast<uint8_t*>(mData) + (i * mBlockSize);
	}
}
BlockAllocator::~BlockAllocator()
{

}
void* BlockAllocator::Allocate()
{

}