#pragma once
#include <unordered_map>
#include "Utilities_global.h"
#include "Object.h"

namespace Utilities
{
    /**
     * @brief The ObjectManager class is responsible for managing all objects in the system.
     */
    class UTILITIES_EXPORT ObjectManager {
    public:
        /**
         * @brief Enumeration of possible errors that can occur while interacting with the object manager.
         */
        enum Error
        {
            none, /**< No error occurred. */
            object_with_ID_already_exists, /**< An object with the given ID already exists in the manager. */
            object_already_in_manager, /**< The object is already in the manager. */
            object_is_nullptr, /**< The object is a nullptr. */
            no_object_with_such_id /**< No object with the given ID exists in the manager. */
        };

        /**
         * @brief Constructs an ObjectManager object.
         */
        ObjectManager();

        /**
         * @brief Destructor for the ObjectManager class.
         */
        ~ObjectManager();

        /**
         * @brief Generates a new unique ID for an object.
         * @return A new unique ID for an object.
         */
        Object::ID generateID();

        /**
         * @brief Adds an object to the object manager.
         * @param obj A pointer to the object to add.
         * @return True if the object was added successfully, false otherwise.
         */
        bool addObject(Object* obj);

        /**
         * @brief Removes an object from the object manager with the given ID.
         * @param id The ID of the object to remove.
         * @return True if the object was removed successfully, false otherwise.
         */
        bool removeObject(Object::ID id);

        /**
         * @brief Checks if an object with the given ID exists in the object manager.
         * @param id The ID of the object to check for.
         * @return True if an object with the given ID exists in the object manager, false otherwise.
         */
        bool exists(Object::ID id);

        /**
         * @brief Returns a pointer to the object with the given ID.
         * @param id The ID of the object to retrieve.
         * @return A pointer to the object with the given ID, or nullptr if no such object exists.
         */
        Object* getObject(Object::ID id) const;

        /**
         * @brief Returns a reference to the object with the given ID.
         * @param id The ID of the object to retrieve.
         * @return A reference to the object with the given ID.
         */
        Object* operator[](Object::ID id) const;

        /**
         * @brief Reserves space for the specified number of objects.
         * @param capacity The number of objects to reserve space for.
         */
        void reserve(size_t capacity);

        /**
         * @brief Returns the number of objects currently in the object manager.
         * @return The number of objects currently in the object manager.
         */
        size_t getObjectCount() const;

        /**
         * @brief Removes all objects from the object manager.
         */
        void clear();

        /**
         * @brief Returns the last error that occurred while interacting with the object manager.
         * @return The last error that occurred while interacting with the object manager.
         */
        Error getLastError() const;

        /**
         * @brief Resets the last error that occurred while interacting with the object manager.
         */
        void resetLastError() const;

        /**
         * @brief An iterator for the object manager.
         */
        class UTILITIES_EXPORT iterator : public std::iterator<std::input_iterator_tag, Object*> 
        {
        private:
            typename std::unordered_map<Object::ID, Object*>::iterator it;

        public:
            /**
            * @brief Constructs an iterator with the given iterator.
            * @param iter The iterator to construct the ObjectManager iterator from.
            */
            iterator(typename std::unordered_map<Object::ID, Object*>::iterator iter);
            /**
             * @brief Advances the iterator to the next object in the manager.
             * @return The updated iterator.
             */
            iterator operator++();

            /**
             * @brief Returns a reference to the object pointed to by the iterator.
             * @return A reference to the object pointed to by the iterator.
             */
            Object*& operator*();

            /**
             * @brief Compares the iterator with another iterator for equality.
             * @param other The other iterator to compare against.
             * @return True if the iterators are equal, false otherwise.
             */
            bool operator==(const iterator& other) const;

            /**
             * @brief Compares the iterator with another iterator for inequality.
             * @param other The other iterator to compare against.
             * @return True if the iterators are not equal, false otherwise.
             */
            bool operator!=(const iterator& other) const;
        };  
        /**
         * @brief Returns an iterator pointing to the first object in the object manager.
         * @return An iterator pointing to the first object in the object manager.
         */
        iterator begin();

        /**
         * @brief Returns an iterator pointing to the end of the object manager.
         * @return An iterator pointing to the end of the object manager.
         */
        iterator end();
    private:
        /**
         * @brief The next ID to be assigned to an object.
         */
        static Object::ID m_nextId;
        /**
         * @brief The map of objects in the object manager, with IDs as the keys.
         */
        std::unordered_map<Object::ID, Object*> m_objects;

        /**
         * @brief The last error that occurred while interacting with the object manager.
         */
        mutable Error m_lastError;
};
}