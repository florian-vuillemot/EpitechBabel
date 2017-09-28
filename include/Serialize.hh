//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_SERIALIZE_H
#define EPITECHBABEL_SERIALIZE_H

#include <memory>
#include "IConfig.hh"

template <typename Type>
class Serialize
{
    using typeSize = unsigned int;

public:
    bool init(IConfig const &) noexcept {
        return true;
    }

    bool create(typeSize size, std::unique_ptr<Type> &&ptr) noexcept  {
        this->size = size;
        this->ptr = std::move(ptr);
    }

    template <typename ... Args>
    bool create(typeSize size, Args* ...ptr) noexcept  {
        this->ptr = std::unique_ptr<Type>(ptr...);
        this->size = size;
    }

    std::unique_ptr<Type> &&getData() noexcept  {
        return std::move(this->ptr);
    }

    typeSize getSize() const noexcept  {
        return this->size;
    }

    bool available() const noexcept  {
        return this->ptr.operator bool();
    }

private:
    std::unique_ptr<Type> ptr;
    typeSize size;
};

#endif //EPITECHBABEL_SERIALIZE_H
