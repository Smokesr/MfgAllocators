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

#include "StackAllocator.hpp"

namespace mfg {
    StackAllocator::StackAllocator(void* memory, const size_t& size) :
        Allocator(memory, size),
        mMarker(0)
    {
        ASSERT(size > 0);
    }

    StackAllocator::~StackAllocator() {}

    void* StackAllocator::allocate(const size_t& size) {
        ASSERT(size > 0);
        ASSERT(mMarker + size <= mSize);

        mMarker += size;

#ifdef MFG_MEMORY_REPORT
        mMrUsed += size;
        mMrNumOfAllocations++;
#endif

        return mMemory + mMarker - size;
    }

    void StackAllocator::deallocate(void* memory) {
        ///do nothing, because you have to use deallocateTo
    }

    void StackAllocator::deallocateTo(Marker marker) {
        ASSERT(marker <= mMarker);

#ifdef MFG_MEMORY_REPORT
        mMrUsed -= mMarker - marker;
        mMrNumOfAllocations--;
#endif

        mMarker = marker;
    }

    void StackAllocator::clear() {
        mMarker = 0;

#ifdef MFG_MEMORY_REPORT
        mMrUsed = 0;
        mMrNumOfAllocations = 0;
#endif
    }

    Marker StackAllocator::getMarker() { return mMarker; }
}//mfg
