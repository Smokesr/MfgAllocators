/*! \file   BlockAllocator.hpp
 *  \brief  Handles different sized blocks.
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

#ifndef MFG_BLOCKALLOCATOR_HPP
#define MFG_BLOCKALLOCATOR_HPP

#include "Allocator.hpp"

//! \namespace  mfg
namespace mfg {
    /*! \class  BlockAllocator
     *  \brief  This class can allocate different size of blocks.
     *          Copy and move constructors and assignments are unavailable.
     */
    class BlockAllocator : public Allocator {
    private:
        struct Block { //mask for blocks
            size_t size;
            Block* next;
        };

        Block* mBlocks; //blocks
    public:
        /*! \fn     BlockAllocator(void* memory, const size_t& size)
         *  \brief  Constructor.
         *  \param  memory The beginning of the memory.
         *  \param  size The size of the memory.
         */
        BlockAllocator(void* memory, const size_t& size);

        BlockAllocator(const BlockAllocator& other) = delete;
        BlockAllocator& operator=(const BlockAllocator& other) = delete;
        BlockAllocator(BlockAllocator&& other) = delete;
        BlockAllocator& operator=(BlockAllocator&& other) = delete;

        /*! \fn ~BlockAllocator()
         *  \brief Destructor.
         */
        ~BlockAllocator();

        /*! \fn     void* allocate(const size_t& size)
         *  \brief  Allocates one block of memory with the specified size.
         *  \param  size
         *  \return The beginning of the memory block.
         */
        void* allocate(const size_t& size) final;

        /*! \fn     void deallocate(void* memory)
         *  \brief  Deallocates the specified memory block.
         *  \param  memory The beginning of the memory block.
         */
        void deallocate(void* memory) final;

        /*! \fn     void clear()
         *  \brief  Deallocates all the previously allocated blocks.
         */
        void clear() final;

        /*! \fn     const size_t& CheckSize(void* memory)
         *  \brief  Check the size of the specified memory block.
         *  \param  memory The beginning of the memory block.
         */
        static const size_t& CheckSize(void* memory);

#ifdef MFG_DEBUG
        /*! \fn     void printSizeOfBlocks()
         *  \brief  Print a list of sizes of blocks.
         *          Only for debug purposes.
         */
        void printSizeOfBlocks();
#endif // MFG_DEBUG
    };
}//mfg

#endif // MFG_BLOCKALLOCATOR_HPP
