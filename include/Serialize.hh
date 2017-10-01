//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_SERIALIZE_H
#define EPITECHBABEL_SERIALIZE_H

#include <memory>
#include "IConfig.hh"

namespace Serialize {
    using bit_field = std::unique_ptr<char[]>;

    template<typename T>
    class Serialize {
    public:
        using type_size = unsigned int;
        using type = T;
        using type_ptr = std::unique_ptr<type>;

    public:
        Serialize &operator=(type_ptr &&ptr) noexcept
        {
            this->ptr = std::move(ptr);
            return *this;
        }

        bool create(type_size size, type_ptr &&ptr) noexcept {
            this->size = size;
            this->ptr = std::move(ptr);
            return true;
        }

        bool create(type_size size, type ptr) noexcept {
            this->ptr = type_ptr(ptr);
            this->size = size;
            return true;
        }

        bool create(type_size size, type *ptr) noexcept {
            this->ptr = type_ptr(ptr);
            this->size = size;
            return true;
        }

        type_ptr &&getData() noexcept {
            return std::move(this->ptr);
        }

        type_size getSize() const noexcept {
            return this->size;
        }

        bool available() const noexcept {
            return this->ptr.operator bool();
        }

    private:
        type_ptr ptr;
        type_size size;
    };

}
#endif //EPITECHBABEL_SERIALIZE_H
