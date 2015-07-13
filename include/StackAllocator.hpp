/*! \file   StackAllocator.hpp
 *  \brief  Handles a stack of memory, and a marker on it.
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

#ifndef MFG_STACKALLOCATOR_HPP
#define MFG_STACKALLOCATOR_HPP

#include "Allocator.hpp"

//! \namespace  mfg
namespace mfg {
    typedef size_t Marker;  //! \typedef    size_t Marker

    /*! \class  StackAllocator
     *  \brief  This class can allocate different size of memory,
     *          but can deallocate it only with a marker.
     *          Copy and move constructors and assignments are unavailable.
     */
    class StackAllocator : public Allocator {
    private:
        size_t mMarker; //current marker
    public:
        /*! \fn     StackAllocator(void* memory, const size_t& size)
         *  \brief  Constructor.
         *  \param  memory The beginning of the memory.
         *  \param  size The size of the memory.
         */
        StackAllocator(void* memory, const size_t& size);

        StackAllocator(const StackAllocator& other) = delete;
        StackAllocator& operator=(const StackAllocator& other) = delete;
        StackAllocator(StackAllocator&& other) = delete;
        StackAllocator& operator=(StackAllocator&& other) = delete;

        /*! \fn ~StackAllocator()
         *  \brief Destructor.
         */
        ~StackAllocator();

        /*! \fn     void* allocate(const size_t& size)
         *  \brief  Allocates memory with the specified size.
         *  \param  size
         *  \return The beginning of the memory.
         */
        void* allocate(const size_t& size);

        /*! \fn     void deallocate(void* memory)
         *  \brief  In this class this method is not working.
         *          Use void deallocateTo(void* memory) instead.
         *  \param  memory
         */
        void deallocate(void* memory);

        /*! \fn     void deallocateTo(Marker marker)
         *  \brief  Deallocate all the items next to marker.
         *  \param  marker
         */
        void deallocateTo(Marker marker);

        /*! \fn     void clear()
         *  \brief  Deallocates all the previously allocated memory.
         */
        void clear();

        /*! \fn     Marker getMarker()
         *  \return The current marker.
         */
        Marker getMarker();
    };
}//mfg
#endif // MFG_STACKALLOCATOR_HPP

