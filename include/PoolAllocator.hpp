/*! \file   PoolAllocator.hpp
 *  \brief  Handles same sized blocks.
 */

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

#ifndef MFG_POOLALLOCATOR_HPP
#define MFG_POOLALLOCATOR_HPP

#include "Allocator.hpp"

//! \namespace  mfg
namespace mfg {
    /*! \class  PoolAllocator
     *  \brief  This class can allocate only the same size of blocks.
     *          Copy and move constructors and assignments are unavailable.
     */
    class PoolAllocator : public Allocator {
    private:
        void** mPool; // memory blocks
        size_t mBlockSize; //size of blocks
    public:
        /*! \fn     PoolAllocator(void* memory, const size_t& size, const size_t& blockSize)
         *  \brief  Constructor.
         *  \param  memory The beginning of the memory.
         *  \param  size The size of the memory.
         *  \param  blockSize Size of blocks. (Must be bigger than the size of a pointer.)
         */
        PoolAllocator(void* memory, const size_t& size, const size_t& blockSize);

        PoolAllocator(const PoolAllocator& other) = delete;
        PoolAllocator& operator=(const PoolAllocator& other) = delete;
        PoolAllocator(PoolAllocator&& other) = delete;
        PoolAllocator& operator=(PoolAllocator&& other) = delete;

        /*! \fn ~PoolAllocator()
         *  \brief Destructor.
         */
        ~PoolAllocator();

        /*! \fn     void* allocate(const size_t& size)
         *  \brief  Allocates exactly one block.
         *  \param  size Can not be bigger than size of a block.
         *  \return The beginning of the memory block.
         */
        void* allocate(const size_t& size) final;

        /*! \fn     void deallocate(void* memory)
         *  \brief  Deallocates the specified memory.
         *  \param  memory The beginning of the memory.
         */
        void deallocate(void* memory) final;

        /*! \fn     void clear()
         *  \brief  Deallocates all the previously allocated blocks.
         */
        void clear() final;

        /*! \fn     const size_t& getBlockSize() const
         *  \return The size of one block.
         */
        const size_t& getBlockSize() const;
    };
}//mfg

#endif // MFG_POOLALLOCATOR_HPP
