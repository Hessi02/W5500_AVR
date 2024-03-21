/**
 *  \file   heap.hpp
 *  \brief  The file adds basic heap functionalities.
 */

#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <stdlib.h>

/**
 *  \fn         operator new(size_t size)
 *  \brief      The function creates a new instance on the heap
 *  \param[in]  size passes the size of the new instance in bytes
 *  \note       The function might return nullptr to avoid heap and stack colliding!
 *
 *  The function allocates memory on the heap and creates a instance of a specific type. The error handling
 *  differs from the usal C++ handling for the new-operator. The operator does not throw the std::bad_alloc
 *  error if the allocation fails. If it fails, the function returns the nullptr to clarify that and error
 *  occured!
 */
inline void* operator new(size_t size)
{
    return malloc(size);
}

/**
 *  \fn         operator delete(void* ptr, unsigned int)
 *  \brief      The function deletes a existing instance from the heap
 *  \param[in]  ptr passes the pointer to the instance to delete from the heap
 *  \param[in]  size passes the target instance count (here: size = 1)
 *
 *  The function deallocates memory on the heap and makes the memory segment reusable. The implmentation uses
 *  the C function free() to copy its behavior.
 */
inline void operator delete(void* ptr, unsigned int size)
{
    free(ptr);
}

#endif //__HEAP_HPP__