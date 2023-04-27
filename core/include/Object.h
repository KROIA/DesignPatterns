#pragma once
#include "DesignPatterns_global.h"

namespace DesignPatterns
{
    class DESIGN_PATTERNS_EXPORT Object {
        friend ObjectManager;
    public:
        Object(size_t id);
        Object(ObjectManager &manager, size_t id);
        Object(ObjectManager &manager);
        virtual ~Object();

        size_t getID() const;

        bool freeFromManager();
        ObjectManager* getManager() const;

    private:

        void notifyDelete();
        void setManager(ObjectManager* manager);

        ObjectManager* m_manager;
        size_t m_id;
    };
}