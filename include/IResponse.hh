//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_IRESPONSE_HH
#define EPITECHBABEL_IRESPONSE_HH

#include <memory>
#include "Serialize.hh"
#include "IConfig.hh"

namespace Response {
    using serialize_type = Serialize::Serialize<char[]>;

    /**
     * Status of request
     */
    class IStatus {
    public:
        virtual ~IStatus() {}

        /**
         * Success of request
         */
        virtual void success() noexcept = 0;

        /**
         * Object correctly create
         */
        virtual void create() noexcept = 0;

        /**
         * Route not allowed
         */
        virtual void notAllow() noexcept = 0;

        /**
         * Your are not authentificate, need authentification
         */
        virtual void notAuth() noexcept = 0;

        /**
         * Route not found
         */
        virtual void notFound() noexcept = 0;

        /**
         * Bad request, formating error...
         */
        virtual void badRequest() noexcept = 0;

        /**
         * Return status code on string
         * @return
         */
        virtual std::string const &status() const noexcept = 0;

        /**
         * Return status serialize
         * @return
         */
        virtual serialize_type::type_ptr serialize() const noexcept = 0;

        /**
         * Load status from serialize data
         * @return
         */
        virtual serialize_type::type_ptr load(serialize_type::type_ptr &&, serialize_type::type_size const) noexcept = 0;

    };

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////

    /**
     * Response object
     */
    class IResponse {
    public:
        using status_type = std::unique_ptr<IStatus>;
        using data_type = std::string;

    public:
        virtual ~IResponse() {}

        /**
        * Hydrate object from serialize object.
        * @return
        */
        virtual bool load(serialize_type &&) noexcept = 0;

        /**
         * Serialize request and return it.
         * @return
         */
        virtual serialize_type serialize() const noexcept = 0;

        /**
         * Set status code of response
         */
        virtual void setStatus(status_type &&) noexcept = 0;

        /**
         * Set data of response
         */
        virtual void setData(data_type const &) noexcept = 0;

        /**
         * Set status code of response
         */
        virtual status_type::element_type const &getStatus() const noexcept = 0;

        /**
         * Set data of response
         */
        virtual data_type const &getData() const noexcept = 0;
    };

} // End namespace

#endif //EPITECHBABEL_IRESPONSE_HH
