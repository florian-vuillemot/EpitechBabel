//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_RESPONSE_HH
#define EPITECHBABEL_RESPONSE_HH

#include <cstdint>
#include <stdint.h>
#include "../../../include/IResponse.hh"

namespace Response
{
    class Response : public IResponse
    {
    public:
        using type_response_info = int32_t;

    public:
        bool load(serialize_type &&) noexcept override ;
        bool serialize(serialize_type &) const noexcept override ;
        void setStatus(status_type const &) noexcept override ;
        void setData(std::string const &) noexcept override ;

    private:
        struct ResponseInfo {
            type_response_info endian;
            type_response_info statusSize;
            type_response_info dataSize;
        };

    private:
        serialize_type::typePtr getResponseInfo(serialize_type::typePtr &&, ResponseInfo &) const noexcept ;
    };
} // End namespace

#endif //EPITECHBABEL_RESPONSE_HH
