/**
 *  \file   callback.hpp
 *  \brief  The file contains declaration for the callback class.
 */

#ifndef __CALLBACK_HPP__
#define __CALLBACK_HPP__

#include "callback_instance.hpp"

/**
 *  \class  Callback 
 *  \brief  The class represents an callback of a callback instance. 
 */
class Callback
{
public:
    Callback(CallbackInstance* instance, void (CallbackInstance::*method)(void))
        : _instance(instance)
        , _method(method)
    {
    }

    template<typename DerivedInstance>
    Callback(DerivedInstance* instance, void (DerivedInstance::*method)(void))
        : _instance(static_cast<CallbackInstance*>(instance))
        , _method(static_cast<void (CallbackInstance::*)(void)>(method))
    {
    }

    void fire(void) { (_instance->*_method)(); }

private:
    CallbackInstance* _instance;
    void (CallbackInstance::*_method)(void);
};

#endif //__CALLBACK_HPP__