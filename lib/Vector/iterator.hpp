/**
 *  \file   iterator.hpp
 *  \brief  The file contains implementation of the class 'Element'.
 *
 *  Even if the implementation requires a .cpp file due to the increased
 *  compilation effort, this is omitted in the vector library. This allows the
 *  container to be used in conjunction with different types. Although it will
 *  be described in more detail later, it should be noted at this point that
 *  large memory allocations should be avoided at all costs. For that reason the
 *  library is well suited for fundamental types like chars.
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "element.hpp"

/**
 *  \class  Iterator
 *  \brief  The class helps iterating over the elements of a Vector.
 *  \tparam ConetentType passes the typename of the stored instances.
 *
 *  The class is mainly used for the use of range for loops. The iterator keeps 
 *  track over the start and end point of the iteration. It also stores the 
 *  current iteration state/index.
 */
template<typename ContentType>
class Iterator
{
public:
    /**
     *  \fn         Iterator(Element<ContentType>* element)
     *  \brief      The constructor initializes an element of type 'Iterator'
     *  \param[in]  element passes the element to take as base of iteration.
     */
    Iterator(Element<ContentType>* element)
        : _currentElement(element)
    {}

    /**
     *  \fn         operator!=(const Iterator& other) const
     *  \brief      Operator for comparing two iterators.
     *  \param[in]  other passes the iterator to compare.
     *  \return     Result of comparison.
     */
    bool operator!=(const Iterator& other) const
    {
        return (_currentElement != other._currentElement->getNextElement());
    }

    /**
     *  \fn         operator*(void) const
     *  \brief      Dereferencing the content at the current iterator position.
     *  \return     Content stored by the underlaying element.
     */
    ContentType operator*(void) const { return _currentElement->getContent(); }

    /**
     *  \fn     operator++(void)
     *  \brief  Incrementing the iterator's position by one.
     *  \return Iterator for the new position (same as before).
     */
    const Iterator& operator++(void)
    {
        _currentElement = _currentElement->getNextElement();
        return *this;
    }

private:
    /**
     *  \var    _currentElement
     *  \brief  Element of Vector at the iterators's current position.
     */
    Element<ContentType>* _currentElement;
};

#endif //__ITERATOR_HPP__