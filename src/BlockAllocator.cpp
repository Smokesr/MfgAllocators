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

#include "BlockAllocator.hpp"

namespace mfg {
    BlockAllocator::BlockAllocator(void* memory, const size_t& size) :
        Allocator(memory, size)
    {
        ASSERT(size > sizeof(Block));

        mBlocks = (Block*) mMemory;
        mBlocks->size = mSize;
        mBlocks->next = nullptr;
    }

    BlockAllocator::~BlockAllocator() {}

    void* BlockAllocator::allocate(const size_t& size) {
        ASSERT(size >= sizeof(Block));
        ASSERT(mBlocks != nullptr);

        size_t newSize = size + sizeof(size_t);

        Block* bestFitPrev = nullptr;
        Block* bestFit = mBlocks;
        Block* block = mBlocks->next;
        Block* prev = mBlocks;

        if(mBlocks->size < newSize && (mBlocks->size - newSize < sizeof(Block) || mBlocks->size - newSize != 0)) {
            bestFit = mBlocks->next;
        }

        while(block != nullptr) {
            if  (block->size >= newSize && //the block is enough
                (block->size - newSize >= sizeof(Block) || block->size - newSize == 0) && //but if we allocate from it, its still enough to became a new block, or completly disappear
                block->size < bestFit->size) //and its fits better.
            {
                bestFit = block;
                bestFitPrev = prev;
            }

            prev = block;
            block = block->next;
        }

        if(bestFit == nullptr) { //there is no block which fit.
            ASSERT(false);
            return nullptr;
        }

        if(bestFit->size - newSize == 0) {
            if(bestFitPrev != nullptr) {
                bestFitPrev->next = bestFit->next;
            }
            else {
                mBlocks = mBlocks->next;
            }
        }
        else {
            block = (Block*)((void*) bestFit + newSize);
            block->size = bestFit->size - newSize;
            block->next = bestFit->next;

            if(bestFitPrev != nullptr) {
                bestFitPrev->next = block;
            }
            else {
                mBlocks = block;
            }
        }

        *((size_t*) bestFit) = newSize;

#ifdef MFG_MEMORY_REPORT
        mMrUsed += newSize;
        mMrNumOfAllocations++;
#endif
        return ((void*) bestFit) + sizeof(size_t);
    }

    void BlockAllocator::deallocate(void* memory) {
        ASSERT(memory != nullptr);

        Block* deallocBlock = (Block*) (memory - sizeof(size_t));
        deallocBlock->next = nullptr;

#ifdef MFG_MEMORY_REPORT
        mMrUsed -= deallocBlock->size;
        mMrNumOfAllocations--;
#endif

        void* memoryEnd =((void*) deallocBlock) + deallocBlock->size;
        Block* block = mBlocks;
        Block* prev = nullptr;

        while(block != nullptr) {
            if((void*) block >= memoryEnd) {
                break;
            }

            prev = block;
            block = block->next;
        }

        if(prev == nullptr) { //before all blocks
            deallocBlock->next = mBlocks;
            mBlocks = deallocBlock;
        }
        else if((void*)prev + prev->size == (void*)deallocBlock) { //exactly next to the previous block
            prev->size += deallocBlock->size;
            deallocBlock->size = 0;
            deallocBlock = prev;
        }
        else { //doesnt match with the previous block
            deallocBlock->next = prev->next;
            prev->next = deallocBlock;
        }

        if(block != nullptr && (void*) block == memoryEnd) { //exactly before the next block
            deallocBlock->size += block->size;
            deallocBlock->next = block->next;
            block->size = 0;
            block->next = nullptr;
        }
    }

    void BlockAllocator::clear() {
        memset(mMemory, 0, mSize);

        mBlocks = (Block*) mMemory;
        mBlocks->size = mSize;
        mBlocks->next = nullptr;
    }

    const size_t& BlockAllocator::CheckSize(void* memory) {
        return *((size_t*) (memory - sizeof(size_t)));
    }

#ifdef MFG_DEBUG
    void BlockAllocator::printSizeOfBlocks() {
        Block* block = mBlocks;
        while(block != nullptr) {
            std::cout << "blockSize: " << block->size << std::endl;
            block = block->next;
        }
    }
#endif // MFG_DEBUG
