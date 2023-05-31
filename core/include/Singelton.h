#pragma once
#include "Utilities_global.h"

namespace Utilities
{
    /**
     *  @brief A template class for creating singleton objects.
     *  @tparam T The type of the singleton object.
     */
    template<class T>
    class Singleton {
    public:
        /*
         *  @brief Returns the instance of the singleton object.
         *  @return The instance of the singleton object.
         */
        static T& getInstance()
        {
            if (!m_instance)
            {
                m_instance = new T();
            }
            return *m_instance;
        }
        static void destroy()
        {
            delete m_instance;
        }
        static const char *getName()
        {
            if (!m_instance)
            {
                m_instance = new T();
            }
            return m_className;
        }

        /**
         *  @brief Deletes the copy constructor of the Singleton class.
         */
        Singleton(const Singleton&) = delete;

        /**
         *  @brief Deletes the assignment operator of the Singleton class.
         */
        Singleton& operator=(const Singleton&) = delete;

        

    protected:
        /**
         *  @brief Constructs a Singleton object.
         */
        Singleton()
            //: m_instance(this)
            //, m_className(typeid(T).name())
        {
           // m_instance = this;
            std::string name(typeid(T).name());
            m_className = new char[name.size()+1];
            strcpy(m_className, name.c_str());
        }

        /**
         *  @brief Destroys the Singleton object.
         */
        ~Singleton()
        {
            m_instance = nullptr;
        }

        static T* m_instance;
        static char* m_className; /**< The name of the class of the singleton object. */
    };

    template<class T>
    T* Singleton<T>::m_instance = nullptr;

    template<class T>
    char* Singleton<T>::m_className = nullptr;


}