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

#include "Allocator.hpp"

namespace mfg {
    Allocator::Allocator(void* memory, const size_t& size) :
        mMemory(memory),
        mSize(size)
    {
        ASSERT(size > 0);

        memset(mMemory, 0, mSize);

#ifdef MFG_MEMORY_REPORT
        mMrUsed = 0;
        mMrNumOfAllocations = 0;
#endif

    }

    Allocator::~Allocator() {}

    bool Allocator::isOutOfMemory() { return mMemory == nullptr; }
    void* Allocator::getMemory() { return mMemory; }
    size_t Allocator::getSize() { return mSize; }

#ifdef MFG_MEMORY_REPORT
    size_t Allocator::getUsedSize() { return mMrUsed; }
    size_t Allocator::getNumberOfAllocations() { return mMrNumOfAllocations; }
#endif

}//mfg
