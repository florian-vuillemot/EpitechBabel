//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_SERIALIZE_H
#define EPITECHBABEL_SERIALIZE_H

#include <memory>
#include "IConfig.hh"

namespace Serialize {

    template<typename T>
    class Serialize {
    public:
        using typeSize = unsigned int;
        using type = T;
        using typePtr = std::unique_ptr<type>;

    public:
        bool init(IConfig const &) noexcept {
            return true;
        }

        bool create(typeSize size, typePtr &&ptr) noexcept {
            this->size = size;
            this->ptr = std::move(ptr);
            return true;
        }

        template<typename ... Args>
        bool create(typeSize size, Args *...ptr) noexcept {
            this->ptr = typePtr(ptr...);
            this->size = size;
            return true;
        }

        typePtr &&getData() noexcept {
            return std::move(this->ptr);
        }

        typeSize getSize() const noexcept {
            return this->size;
        }

        bool available() const noexcept {
            return this->ptr.operator bool();
        }

    private:
        typePtr ptr;
        typeSize size;
    };

}
#endif //EPITECHBABEL_SERIALIZE_H
