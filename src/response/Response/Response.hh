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
    class Response : public IResponse {
    public:
        using type_response_info = uint32_t;

    public:
        Response() = default;
        ~Response() = default;
        Response(Response &&) = default;
        Response(Response const &) = default;
        Response& operator=(Response &&) = default;
        Response& operator=(Response const &) = default;

        bool load(serialize_type &&) noexcept override;
        serialize_type serialize() const noexcept override;
        void setStatus(status_type &&) noexcept override;
        void setData(data_type const &) noexcept override;
        status_type::element_type const &getStatus() const noexcept override ;
        data_type const &getData() const noexcept override ;

    private:
        struct ResponseInfo {
            type_response_info statusSize;
            type_response_info dataSize;
            static constexpr type_response_info size = sizeof(type_response_info) << 1;

            ResponseInfo() = default;
            ~ResponseInfo() = default;
            ResponseInfo(ResponseInfo &&) = default;
            ResponseInfo(ResponseInfo const &) = default;
            ResponseInfo& operator=(ResponseInfo const &) = default;
            ResponseInfo& operator=(ResponseInfo &&) = default;

            auto getSizeResponse() const noexcept -> decltype(ResponseInfo::statusSize + ResponseInfo::dataSize + ResponseInfo::size);
            auto getPlaceStatus() const noexcept -> decltype(ResponseInfo::size);
            auto getPlaceData() const noexcept -> decltype(ResponseInfo::statusSize + ResponseInfo::size);
            auto getSizeBody() const noexcept -> decltype(ResponseInfo::statusSize + ResponseInfo::dataSize);
        };

        struct ResponseBody {
            status_type statusCode;
            data_type data;

            ResponseBody() = default;
            ~ResponseBody() = default;
            ResponseBody(ResponseBody &&) = default;
            ResponseBody(ResponseBody const &) = default;
            ResponseBody& operator=(ResponseBody const &) = default;
            ResponseBody& operator=(ResponseBody &&) = default;
        };


    private:
        serialize_type::type_ptr getResponseInfo(serialize_type::type_ptr &&, ResponseInfo const &) const noexcept;
        serialize_type::type_ptr setResponseInfo(serialize_type::type_ptr &&, ResponseInfo &) const noexcept;
        serialize_type::type_ptr getResponseBody(serialize_type::type_ptr &&, ResponseInfo const &, ResponseBody const &) const noexcept ;
        serialize_type::type_ptr setResponseBody(serialize_type::type_ptr &&, ResponseInfo const &, ResponseBody &) const noexcept ;

    private:
        ResponseInfo infos;
        ResponseBody body;
    };
} // End namespace

#endif //EPITECHBABEL_RESPONSE_HH
