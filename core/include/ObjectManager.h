#pragma once
#include <unordered_map>
#include "DesignPatterns_global.h"
#include "Object.h"

namespace DesignPatterns
{
    class DESIGN_PATTERNS_EXPORT ObjectManager {
    public:
        enum Error
        {
            none,
            object_with_ID_already_exists,
            object_already_in_manager,
            object_is_nullptr,
            no_object_with_such_id
        };

        ObjectManager();
        ~ObjectManager();

        size_t generateID();

        bool addObject(Object* obj);
        bool removeObject(size_t id);
        bool exists(size_t id);
        Object* getObject(size_t id) const;
        Object* operator[](size_t id) const;

        size_t getObjectCount() const;
        void clear();

        Error getLastError() const;
        void resetLastError() const;

        


        class DESIGN_PATTERNS_EXPORT iterator : public std::iterator<std::input_iterator_tag, Object*> {
        private:
            typename std::unordered_map<size_t, Object*>::iterator it;

        public:
            iterator(typename std::unordered_map<size_t, Object*>::iterator iter);
            iterator operator++();
            Object*& operator*();
            bool operator==(const iterator& other) const;
            bool operator!=(const iterator& other) const;
        };

        iterator begin();
        iterator end();


    private:
        static size_t m_nextId;
        std::unordered_map<size_t, Object*> m_objects;
        mutable Error m_lastError;
    };
}