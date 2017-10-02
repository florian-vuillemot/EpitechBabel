#ifndef IMANAGER_HH
#define IMANAGER_HH

#include <vector>

namespace Manager {

    template <typename T, typename ContainerType>
    class IManager {
    public:
        using value_type = T;
        using container_type = ContainerType;
        using const_iterator = typename container_type::const_iterator;

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
         * Return a vector of elements.
         * @return
         */
        virtual container_type   const &get() const noexcept = 0;

        /**
         * Return the iterator of element if find.
         * @param val
         * @return
         */
        virtual const_iterator get(const value_type &val) const noexcept = 0;
    };
}

#endif