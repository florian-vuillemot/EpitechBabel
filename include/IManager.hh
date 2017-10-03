#ifndef IMANAGER_HH
#define IMANAGER_HH

#include <vector>

namespace Manager {
    template <typename T>
    class IManager {
    public:
        using value_type = T;

        /**
         * Push element if not exist method
         * @param val
         */
        virtual void push(value_type &val) = 0;
        virtual void push(value_type &&val) = 0;

        /**
         * Find a element in vector
         * @param val
         * @return
         */
        virtual bool exist(const value_type &val) const noexcept = 0;

        /**
        * Remove element if found
        * @param val
        * @return true if found
        */
        virtual bool remove(const value_type &val) noexcept = 0;

        /**
         * Return the element or throw
         * @param val
         * @return
         * @throw
         */
        virtual value_type &get(const value_type &val) const = 0;

        /**
         * Return element at place.
         * @param place
         * @return
         */
        virtual value_type &at(const int place) const = 0;
    };
}

#endif