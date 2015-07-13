/*! \file   Allocator.hpp
 *  \brief  Provide interface to use allocators.
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

#ifndef MFG_ALLOCATOR_HPP
#define MFG_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "mfg.hpp"

//! \namespace  mfg
//! \def    MFG_MEMORY_REPORT   If defined, then you can use the memory report functions.
//! \def    MFG_DEBUG           If defined assertions will work.
namespace mfg {
    /*! \class  Allocator
     *  \brief  The parent of all allocator classes. Describe an interface
     *          to treat different types of allocators the same.
     *          Copy and move constructors and assignments are unavailable.
     */
    class Allocator {
    protected:
        /*! \fn     Allocator(void* memory, const size_t& size)
         *  \brief  Constructor for child classes.
         *  \param  memory The beginning of the memory.
         *  \param  size The size of the memory.
         */
        Allocator(void* memory, const size_t& size);

        void* mMemory;  //! \var    mMemory The beginning of the memory block.
        size_t mSize;   //! \var    mSize The size of the memory block.

#ifdef MFG_MEMORY_REPORT
        size_t mMrUsed;                 //! \var    mMrUsed Size of memory in use.
        uint32_t mMrNumOfAllocations;   //! \var    mMrNumOfAllocations
#endif
    public:
        Allocator(const Allocator& other) = delete;
        Allocator& operator=(const Allocator& other) = delete;
        Allocator(Allocator&& other) = delete;
        Allocator& operator=(Allocator&& other) = delete;

        /*! \fn ~Allocator()
         *  \brief Destructor.
         */
        virtual ~Allocator();

        /*! \fn     void* allocate(const size_t& size)
         *  \brief  Pure virtual method for allocating memory.
         *  \param  size Required size of memory.
         *  \return The beginning of the memory.
         */
        virtual void* allocate(const size_t& size) = 0;

        /*! \fn     void deallocate(void* memory)
         *  \brief  Pure virtual method for deallocating memory.
         *  \param  memory The beginning of the memory.
         */
        virtual void deallocate(void* memory) = 0;

        /*! \fn     void clear()
         *  \brief  Pure virtual method for deallocating all the
         *          previously allocated memory.
         */
        virtual void clear() = 0;

        /*! \fn     bool isOutOfMemory()
         *  \return True if there is no more allocatable memory, otherwise false.
         */
        bool isOutOfMemory();

        /*! \fn     void* getMemory()
         *  \return A pointer to the memory block.
         */
        void* getMemory();

        /*! \fn     size_t getSize()
         *  \return The size of the memory block.
         */
        size_t getSize();

#ifdef MFG_MEMORY_REPORT
        /*! \fn     size_t getUsedSize()
         *  \return The size of memory in use.
         */
        size_t getUsedSize();

        /*! \fn     size_t getNumberOfAllocations()
         *  \return The number of allocations.
         */
        size_t getNumberOfAllocations();
#endif
    };

    static Allocator* defaultAllocator = nullptr;
}//mfg
#endif // MFG_ALLOCATOR_HPP
