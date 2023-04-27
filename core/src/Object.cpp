#include "Object.h"
#include "ObjectManager.h"

namespace DesignPatterns
{
    Object::Object(size_t id)
        : m_manager(nullptr)
        , m_id(id)
    {

    }
    Object::Object(ObjectManager& manager, size_t id)
        : m_manager(&manager)
        , m_id(id) 
    {
        if (m_manager)
        {
            m_manager->addObject(this);
        }
    }
    Object::Object(ObjectManager& manager)
        : m_manager(&manager)
        , m_id(manager.generateID())
    {
        if (m_manager)
        {
            m_manager->addObject(this);
        }
    }
    Object::~Object()
    {
        notifyDelete();
    }

    size_t Object::getID() const 
    {
        return m_id;
    }
    bool Object::freeFromManager()
    {
        if (m_manager)
            return m_manager->removeObject(m_id);
        return false;
    }
    ObjectManager* Object::getManager() const
    {
        return m_manager;
    }

    void Object::notifyDelete()
    {
        freeFromManager();
    }
    void Object::setManager(ObjectManager* manager)
    {
        m_manager = manager;
    }
}