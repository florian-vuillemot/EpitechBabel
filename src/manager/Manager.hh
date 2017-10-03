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

#include <stdexcept>
#include <algorithm>
#include "../../include/IManager.hh"


#include <iostream>
namespace Manager {
    template<typename T>
    class Manager: public IManager<T> {
    public:
        using container_type = std::vector<T>;
        using value_type = typename IManager<T>::value_type ;
        using const_iterator = typename container_type::iterator ;


        void push(value_type &val) override {
            if (!this->exist(val)) {
                this->container.push_back(val);
            }
        }

        void push(value_type &&val) override {
            if (!this->exist(val)) {
                this->container.push_back(std::move(val));
            }
        }

        bool exist(const value_type &val) const noexcept override {
            return this->getIt(val) != this->container.end();
        }


        bool remove(const value_type &val) noexcept override {
            auto const &it = this->getIt(val);

            if (it != this->container.end()) {
                this->container.erase(it);
                return true;
            }

            return false;
        }

        value_type &get(const value_type &val) const override {
            auto res = this->getIt(val);

            if (res == this->container.end()){
                throw std::out_of_range("Not exist in container");
            }

            return *res;
        }

        value_type &at(const int place) const override {
            return *this->container.at(place);
        }

    private:
        container_type const &get() const noexcept {
            return this->container;
        }


        const_iterator &getIt(const value_type &val) const noexcept {
            return std::find(this->container.begin(), this->container.end(), val);
        }

    private:
        container_type container;
    };
}
#endif //EPITECHBABEL_IMANAGER_HPP
