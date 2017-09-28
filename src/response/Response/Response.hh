//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_RESPONSE_HH
#define EPITECHBABEL_RESPONSE_HH

#include <stdint.h>
#include "../../../include/IResponse.hh"

namespace Response
{
    class Response : public IResponse
    {
    public:
        bool load(serializeType &&) noexcept override ;
        serializeType &&serialize() const noexcept override ;
        void setStatus(statusType &&) noexcept override ;
        void setData(std::string const &) noexcept override ;
    };
} // End namespace

#endif //EPITECHBABEL_RESPONSE_HH
