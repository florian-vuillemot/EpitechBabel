#ifndef IREQUEST_HH
#define IREQUEST_HH

#include <map>
#include <memory>

#include "Serialize.hh"

namespace Request
{
    class IRequest
    {
    public:
        using header_type = std::map<std::string, std::string>;
        using route_type = std::map<std::string, std::string>;
        using data_type = std::map<std::string, std::string>;
        using bitfield_type = Serialize::bit_field;
        using serialize_type = Serialize::Serialize<bitfield_type::element_type>;


    public:
        virtual ~IRequest(){}

        /**
         * Set the header of request
         */
        virtual void setHeader(header_type const &) noexcept = 0;

        /**
         * Set the request route
         */
        virtual void setRoute(route_type const &) noexcept = 0;

        /**
         * Set the data request
         */
        virtual void setData(data_type const &) noexcept = 0;

        /**
         * Serialize the request
         */
        virtual bitfield_type serialize() const noexcept = 0;

        /**
         * Load the request
         */
        virtual void load(bitfield_type &&) noexcept = 0;
    };
}


#endif