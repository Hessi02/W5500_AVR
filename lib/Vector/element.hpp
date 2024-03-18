/**
 *  \file   element.hpp
 *  \brief  The file contains implementation of the class 'Element'.
 * 
 *  Even if the implementation requires a .cpp file due to the increased 
 *  compilation effort, this is omitted in the vector library. This allows the 
 *  container to be used in conjunction with different types. Although it will 
 *  be described in more detail later, it should be noted at this point that 
 *  large memory allocations should be avoided at all costs. For that reason the 
 *  library is well suited for fundamental types like chars.
 */

#ifndef __ELEMENT_HPP__
#define __ELEMENT_HPP__

/**
 *  \class  Element
 *  \brief  The class represents an element of the container.
 *  \tparam ConetentType passes the typename of the instance to store.
 *
 *  The class 'Element' represents a element in the 'Vector' container. Every
 *  element stores one object of a specified type. The element has a
 *  pointer to the next element in the linked list. To reach dynamic memory
 *  storage, the element must be created on the heap.
 */
template <typename ContentType>
class Element
{
public:
    /**
     *  \fn         Element(const ContentType content, Element* nextElement)
     *  \brief      Intializes the instance of type 'Element'.
     *  \param[in]  content passes the instance to store.
     *  \param[in]  nextElement passes the next element to store.
     * 
     *  At this point, the constructor only initializes the content to store and 
     *  the next element. When implementing a doubly linked list later on, a 
     *  pointer to the previous element must be added.
     */
    Element(const ContentType content, Element* nextElement) : 
        _content(content), _nextElement(nextElement)
    {}

    /**
     *  \fn     getContent(void)
     *  \brief  Getter method for the content.
     *  \return Reference to the stored instance.
     *  \todo   Avoid getter method (anti-pattern).
     * 
     *  The method returns the elements content. Even though the getter method
     *  is an anti-pattern, it is used widely in the library for that reason
     *  the method is explicitly not marked as deprecated. Nontheless the method
     *  should be avoid for new implementations. To do this, responsibilities 
     *  must be outsourced to the 'Element' class.
     */
    ContentType& getContent(void)
    {
        return _content;
    }

    /**
     *  \fn     getNextElement(void)
     *  \brief  Getter method for the container's next element.
     *  \return Pointer to the next element.
     *  \todo   Avoid getter method (anti-pattern).
     * 
     *  The method returns the next element in the singly linked list. Like the 
     *  previous method, this getter is also an anti-pattern. Removing this 
     *  getter is particularly useful when implementing a doubly linked list. 
     *  To do this, responsibilities must be outsourced to the 'Element' class.
     */
    Element* getNextElement(void) const
    {
        return _nextElement;
    }    

    /**
     *  \fn         setNextElement(Element* nextElement)
     *  \brief      Setter method for the container's next element.
     *  \param[in]  nextElement passes the nextElement set.
     *  \todo       Avoid setter method (anti-pattern).
     * 
     *  The method sets the next element. This setter method may be even worse 
     *  than the previous getter methods. It allows the vector class direct 
     *  access to private members of the class. At this point, public member 
     *  variables could also be easily introduced. This must be avoided at all 
     *  costs.
     */
    void setNextElement(Element* nextElement)
    {
        _nextElement = nextElement;
    }

private:    
    /**
     *  \var    _content
     *  \brief  The member stores the target instance.
     * 
     *  The variable contains the content of the corresponding template type. 
     *  The memory requirement of the element is therefore directly dependent 
     *  on the memory requirement of the corresponding template type.
     */
     ContentType _content;

    /**
     *  \var    _nextElement
     *  \brief  The member stores a pointer to the container's next element.
     * 
     *  The variable contains the pointer to the next element in the singly 
     *  list. The descriptor should be changed when implementing the doubly
     *  linked list.
     */
    Element* _nextElement;
};

#endif //__ELMENENT_HPP__