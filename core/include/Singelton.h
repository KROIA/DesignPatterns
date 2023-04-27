#pragma once
#include "DesignPatterns_global.h"

namespace DesignPatterns
{
    template<class T>
    class Singleton {
    public:
        static T& getInstance() {
            static T instance;
            return instance;
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

    protected:
        Singleton()
            : m_className(typeid(T).name())
        {

        }
        ~Singleton() = default;

        const char* m_className;
    };
}