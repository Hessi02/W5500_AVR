/**
 *  \file   vector.hpp
 *  \brief  The file contains implementation of the class 'Vector'.
 *
 *  Even if the implementation requires a .cpp file due to the increased compilation effort,
 *  this is omitted in the vector library. This allows the container to be used in conjunction
 *  with different types. Although it will be described in more detail later, it should be
 *  noted at this point that large memory allocations should be avoided at all costs. For that
 *  reason the library is well suited for fundamental types like chars.
 */

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <stdint.h>

#include "element.hpp"
#include "heap.hpp"

/**
 *  \class  Vector
 *  \brief  Container for multiple elements of the linked list.
 *  \tparam ContentType passes the typename of the instances to store.
 *  \see    Element
 *  \todo   Implement range-for-loop.
 *  \todo   Implement doubly linked list.
 *
 *  The class 'Vector' stores multiple objects of same type. The linked list can change
 *  its size dynamically. If an objects gets appended, a element is created on the heap.
 *  The pointer gets the new head of the container, and can be easily acessed by dereferncing
 *  the pointer. The class should be used in a very specific way. For example it shouldn't be
 *  used much to avoid large allocations causing memory errors. Use should be made in the
 *  innermost block to make sure the memory gets deallocated at the earliest time.
 */
template<typename ContentType>
class Vector
{
public:
    /**
     *  \fn     Vector(void)
     *  \brief  The constructor intializes the instance of type 'Vector'.
     *
     *  At this point, the constructor only initializes the head of the stack. However, it
     *  is planned to implement heap-specific monitoring and control functions. An example
     *  of this would be calculating the storage capacity with particular reference to the
     *  storage requirement of an element of the vector.
     */
    Vector(void)
        : _headOfStack(nullptr)
    {}

    /**
     *  \fn     ~Vector(void)
     *  \brief  Removes the container from the AVR's memory.
     *
     *  This specific destructor of the vector class was tested with different template types
     *  as part of another project. The aim is to completely free all allocated memory areas
     *  when deleting the vector. This is done by iterating over the vector elements and
     *  gradually removing them from the heap using the delete operator.
     */
    virtual ~Vector(void)
    {
        Element<ContentType>* nextElement = _headOfStack;

        while (nextElement) {
            Element<ContentType>* currentElement = nextElement;
            nextElement = nextElement->getNextElement();
            delete currentElement;
        }
    }

    /**
     *  \fn         append(const ContentType value)
     *  \brief      The method adds a new element to the top of the linked list.
     *  \param[in]  value passes the instance of template type to store.
     *
     *  The append method appends another instance of the template type to the vector. It
     *  receives the new last index of the container. The new element is given a pointer to
     *  the previous head of the stack and the new element is then made the new head of the
     *  stack. Pass-by-reference is not used because, in combination with this in the
     *  element's constructor, this leads to unauthorized memory access to memory areas that
     *  have already been released. For this reason, the method does not affect the passed
     *  parameter in any way.
     */
    void append(const ContentType value)
    {
        Element<ContentType>* newElement = new Element<ContentType>(value, _headOfStack);
        _headOfStack = newElement;
    }

    /**
     *  \fn     length(void)
     *  \brief  The method calcualtes the length of the linked list.
     *  \return Count of elements contained by the linked list.
     *
     *  The method iterates over the vector elements until the nullptr is reached. Therefore
     *  it is absolutely necessary that the end of the vector is terminated with the nullptr
     *  at all times. If this is not the case, for example due to an element that has already
     *  been deallocated, unauthorized memory accesses will occur. For this purpose, a
     *  validation method for vector elements would be conceivable.
     */
    uint8_t length(void) const
    {
        uint8_t loopIterations = 0;
        Element<ContentType>* nextElement = _headOfStack;

        while (nextElement) {
            nextElement = nextElement->getNextElement();
            loopIterations++;
        }

        return loopIterations;
    }

    /**
     *  \fn         at(const uint8_t& index) const
     *  \brief      The method returns the value at the passed index.
     *  \param[in]  index passes the index of the target value.
     *  \return     The value at the given index.
     *
     *  The method calls the element at the passed index using the 'elementAt()' method.
     *  The content is then read from this and returned. The method used abstracts the
     *  functionality and prevents redundant code. Changes must therefore be made in the
     *  method used.
     */
    ContentType& at(const uint8_t& index) const
    {
        Element<ContentType>* targetElement = elementAt(index);
        return targetElement->getContent();
    }

    /**
     *  \fn         deleteAll(void)
     *  \brief      The method deletes all elements in the linked list.
     *
     *  The method iterates backwards over the method and applies the delete operator to
     *  the respective elements. The reverse iteration is necessary to maintain the
     *  iteration direction of the list elements for further deletion. It is not necessary
     *  to overwrite the deallocated memory areas with the nullptr, as the instances can
     *  then no longer be accessed and therefore dereferenced.
     */
    void deleteAll(void)
    {
        const uint8_t elementCount = length();

        for (uint8_t i = 0; i < elementCount; i++) {
            Element<ContentType>* elementPointer = elementAt(i);
            delete elementPointer;
        }

        _headOfStack = nullptr;
    }

    /**
     *  \fn         insert(const ContentType content, const uint8_t& index)
     *  \brief      The method inserts a object of ContentType into the array.
     *  \param[in]  content passes a pointer to the content to insert.
     *  \param[in]  index passes the index to insert to.
     *  \note       Linus Torvalds would hate me if he saw this...
     *
     *  The method inserts an element at the given location. First an instance is created at
     *  the head of the vector. Then, depending on the given index, the previous and next
     *  elements are specified. The method can certainly be made more elegant. The double
     *  if-else condition makes the code difficult to understand. The query should at least
     *  be merged into a common if condition.
     */
    void insert(const ContentType content, const uint8_t& index)
    {
        Element<ContentType>* newElement = new Element<ContentType>(content, _headOfStack);

        if (index > 0) {
            newElement->setNextElement(elementAt(index - 1));
        } else {
            newElement->setNextElement(nullptr);
        }

        if (!(index >= length() - 1)) {
            Element<ContentType>* elementAfter = elementAt(index);
            elementAfter->setNextElement(newElement);
        } else {
            _headOfStack = newElement;
        }
    }

protected:
    /**
     *  \deprecated
     *  \fn             appendThenDelete(Container<ContentType>* anotherVector)
     *  \brief          The method appends another vector and deletes the passed vector.
     *  \param[inout]   anotherVector passes the vector to append.
     *  \note           The passed vector gets deleted! Only pass vectors created on the heap!
     *
     *  The method copies every element from the passed vector at the end of the container.
     *  The destructor of the given vector is then called. The usefulness of the method is
     *  questionable. A simple overload of the append method is certainly more effective.
     *  The user can then release the memory area independently. The method is therefore
     *  marked as 'deprecated'.
     */
    [[deprecated("To be replaced by append(). Avoid usage, method might get removed.")]] void
    appendThenDelete(Vector<ContentType>* anotherVector)
    {
        for (uint8_t i = 0; i < anotherVector->length(); i++) {
            append(anotherVector->at(i));
        }

        delete anotherVector;
    }

private:
    /**
     *  \fn         elementAt(const uint8_t& index) const
     *  \brief      The method searches the element at the passed index.
     *  \param[in]  index passes the index of the target element.
     *  \return     A pointer to the target element of template type.
     *  \todo       Avoid insecure memory access.
     *
     *  The method iterates over the given number of elements. This is done backwards because
     *  the iteration direction must be followed. The method contains a flaw: If the length of
     *  the vector is zero and the method is applied to it, the nullprtr is dereferenced,
     *  which represents an illegal memory access. This requires further consideration.
     */
    Element<ContentType>* elementAt(const uint8_t& index) const
    {
        const uint8_t itertaionsFromTop = length() - index - 1;

        Element<ContentType>* elementPointer = _headOfStack;

        for (uint8_t i = 0; i < itertaionsFromTop; i++) {
            elementPointer = elementPointer->getNextElement();
        }

        return elementPointer;
    }

    /**
     *  \var    _headOfStack
     *  \brief  The member stores a pointer to the element on the top of the linked list.
     *
     *  The head of the stack represents the entry point of the linked list. If the nullptr
     *  is the head of the stack, the vector is empty. The head of the stack must never
     *  contain a deallocated element.
     */
    Element<ContentType>* _headOfStack;
};

#endif //__VECTOR_HPP__