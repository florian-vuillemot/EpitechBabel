//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_IRESPONSE_HH
#define EPITECHBABEL_IRESPONSE_HH

#include <memory>
#include "IConfig.hh"

template <typename T>
class ISerialize
{

};

namespace Response {
    /**
     * Status of request
     */
    class IStatus {
    public:
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
         * Return status code on int
         * @return
         */
        virtual int statusCode() noexcept = 0;

        /**
         * Return status code on string
         * @return
         */
        virtual std::string const &status() noexcept = 0;
    };

    class IResponse {
    protected:
        using statusType = std::unique_ptr<IStatus>;
        using serializeType = std::unique_ptr <ISerialize<void>>;

    public:
        /**
        * Hydrate object from serialize object.
        * @return
        */
        virtual bool load(serializeType &&) noexcept = 0;

        /**
         * Serialize request and return it.
         * @return
         */
        virtual serializeType &&serialize() const noexcept = 0;

        /**
         * Set status code of response
         */
        virtual void setStatus(statusType &&) noexcept = 0;

        /**
         * Set data of response
         */
        virtual void setData(std::string const &) noexcept = 0;
    };

} // End namespace

#endif //EPITECHBABEL_IRESPONSE_HH
