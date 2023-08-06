#pragma once
namespace DubEngine::Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(const char* name, size_t blockSiz,size_t capacity);
		virtual ~BlockAllocator();

		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator(const BlockAllocator&&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);
	private:
		std::string mName;
		std::vector<void*> mFreeBlocks;

		void* mData = nullptr;
		size_t mBlockSize = 0;
		size_t mCapacity = 0;
		size_t mBlockAllocatedCurrent = 0;
		size_t mBlockAllocatedTotal = 0;
		size_t mBlocksFreed = 0;
		size_t mBlocksHighest = 0;
	};
}