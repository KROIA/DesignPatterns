#pragma once
#include "DesignPatterns_global.h"

namespace DesignPatterns
{
  /**
   * @brief The Object class is a base class for all objects in the system.
   *        It has a unique ID associated with each instance.
   */
    class DESIGN_PATTERNS_EXPORT Object {
        friend ObjectManager;
    public:
        /**
         * @brief The ID type used for identifying objects.
         */
        typedef unsigned long ID;

        /**
         * @brief Constructs an object with the given ID.
         * @param id The unique ID of the object.
         */
        Object(ID id);

        /**
         * @brief Constructs an object with the given ID and adds it to the given object manager.
         * @param manager The object manager to add the object to.
         * @param id The unique ID of the object.
         */
        Object(ObjectManager& manager, ID id);

        /**
         * @brief Constructs an object and adds it to the given object manager.
         * @param manager The object manager to add the object to.
         */
        Object(ObjectManager& manager);

        /**
         * @brief Destructor for the Object class.
         */
        virtual ~Object();

        /**
         * @brief Returns the unique ID of the object.
         * @return The unique ID of the object.
         */
        ID getID() const;

        /**
         * @brief Frees the object from the object manager.
         * @return True if the object was freed successfully, false otherwise.
         */
        bool freeFromManager();

        /**
         * @brief Returns a pointer to the object manager associated with the object.
         * @return A pointer to the object manager associated with the object.
         */
        ObjectManager* getManager() const;

    private:
        /**
         * @brief Notifies the object manager that the object has been deleted.
         */
        void notifyDelete();

        /**
         * @brief Sets the object manager associated with the object.
         * @param manager A pointer to the object manager to set.
         */
        void setManager(ObjectManager* manager);

        ObjectManager* m_manager; /**< A pointer to the object manager associated with the object. */
        ID m_id; /**< The unique ID of the object. */
    };
}