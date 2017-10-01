//
// Created by florian on 30/09/17.
//

#ifndef EPITECHBABEL_STATUS_HH
#define EPITECHBABEL_STATUS_HH

#include <map>
#include "IResponse.hh"

namespace Response
{
    class Status: public IStatus{
    private:
        enum eStatusCode {
            Success = 200, Create = 201, NotAllow = 403,
            NotAuth = 401, BadRequest = 400, NotFound = 404
        };
        std::map<std::string, eStatusCode> _statusCode = {
                {"200", Success}, {"201", Create}, {"403", NotAllow},
                {"401", NotAuth}, {"400", BadRequest}, {"404", NotFound}
        };


    public:
        Status();
        ~Status() = default;
        Status(Status &&) = default;
        Status(Status const &) = default;
        Status &operator=(Status &&) = default;
        Status &operator=(Status const &) = default;

        void success() noexcept override ;
        void create() noexcept override ;
        void notAllow() noexcept override ;
        void notAuth() noexcept override ;
        void notFound() noexcept override ;
        void badRequest() noexcept override ;
        std::string const &status() const noexcept override ;
        serialize_type::type_ptr serialize() const noexcept override ;
        serialize_type::type_ptr load(serialize_type::type_ptr &&, serialize_type::type_size const) noexcept override ;

    private:
        void setStatus(eStatusCode) noexcept ;
        void setStatus(std::string const &) noexcept ;

    private:
        eStatusCode _status;
    };
}

#endif //EPITECHBABEL_STATUS_HH
