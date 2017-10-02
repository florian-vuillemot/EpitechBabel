/*
** IManager.hpp for EpitechBabel in /home/delrivm/EpitechBabel/Manager/IManager.hpp
**
** Made by Matthieu Delrive
** Login   <matthieu.delrive@epitech.eu>
**
** Started on  Tue Sep 26 13:25:02 2017 Matthieu Delrive
** Last update Tue Sep 26 13:25:02 2017 Matthieu Delrive
*/



#ifndef EPITECHBABEL_IMANAGER_HPP
#define EPITECHBABEL_IMANAGER_HPP

#include "../../include/IManager.hh"
#include <algorithm>

namespace Manager {
    template<typename T>
    class Manager: public IManager<T, std::vector<T>> {
    public:
        using container_type = std::vector<T>;
        using value_type = typename IManager<T, container_type>::value_type ;
        using const_iterator = typename IManager<T, std::vector<T>>::const_iterator ;


        void push(value_type &val) {
            if (!this->exist(val)) {
                this->container.push_back(val);
            }
        }

        void push(value_type &&val) {
            if (!this->exist(val)) {
                this->container.push_back(std::move(val));
            }
        }

        bool exist(const value_type &val) const noexcept {
            return this->get(val) != this->container.end();
        }


        bool remove(const value_type &val) noexcept {
            auto const &it = this->get(val);

            if (it != this->container.end()) {
                this->container.erase(it);
                return true;
            }

            return false;
        }

        container_type const &get() const noexcept {
            return this->container;
        }


        const_iterator get(const value_type &val) const noexcept {
            return std::find(this->container.begin(), this->container.end(), val);
        }

    private:
        container_type container;
    };
}
#endif //EPITECHBABEL_IMANAGER_HPP
