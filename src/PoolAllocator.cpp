/*
Copyright (c) 2015 Máté Vágó
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "PoolAllocator.hpp"

namespace mfg {
    PoolAllocator::PoolAllocator(void* memory, const size_t& size, const size_t& blockSize) :
        Allocator(memory, size),
        mPool(nullptr),
        mBlockSize(blockSize)
    {
        ASSERT(blockSize >= sizeof(void*));

        clear();
    }

    PoolAllocator::~PoolAllocator() {}

    void* PoolAllocator::allocate(const size_t& size) {
        ASSERT(mMemory != nullptr);
        ASSERT(size <= mBlockSize);

        void* temp = mPool;
        mPool = (void**) *mPool;

#ifdef MFG_MEMORY_REPORT
        mMrUsed += mBlockSize;
        mMrNumOfAllocations++;
#endif

        return temp;
    }

    void PoolAllocator::deallocate(void* memory) {
        memset(memory, 0, mBlockSize);
        *((void**) memory) = mPool;
        mPool = (void**) memory;

#ifdef MFG_MEMORY_REPORT
        mMrUsed -= mBlockSize;
        mMrNumOfAllocations--;
#endif
    }

    void PoolAllocator::clear() {
        memset(mMemory, 0, mSize);

        size_t numberOfBlocks = mSize / mBlockSize;
        mPool = (void**) mMemory;
        for(size_t i = 0; i < numberOfBlocks; i++) {
            *mPool = (void*) mPool + mBlockSize;
            mPool = (void**) *mPool;
        }

        *mPool = nullptr;
        mPool = (void**) mMemory;
    }
}//mfg
