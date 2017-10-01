//
// Created by florian on 30/09/17.
//

#include "Status.hh"
#include "SerializeParse.hh"

namespace Response
{
    Status::Status() {this->setStatus(NotFound);}
    void Status::success() noexcept {this->setStatus(Success);}
    void Status::create() noexcept{this->setStatus(Create);}
    void Status::notAllow() noexcept{this->setStatus(NotAllow);}
    void Status::notAuth() noexcept{this->setStatus(NotAuth);}
    void Status::notFound() noexcept{this->setStatus(NotFound);}
    void Status::badRequest() noexcept{this->setStatus(BadRequest);}

    std::string const &Status::status() const noexcept
    {
        for (auto const &i: this->_statusCode)
        {
            if (i.second == this->_status){
                return i.first;
            }
        }

        return this->_statusCode.begin()->first;
    }

    serialize_type::type_ptr Status::serialize() const noexcept
    {
        Serialize::SerializeParse parseTool;
        decltype(auto) status = this->status();

        return std::move(parseTool.toBitField(status, status.size()));
    }

    serialize_type::type_ptr Status::load(serialize_type::type_ptr &&ptr, serialize_type::type_size const size) noexcept
    {
        Serialize::SerializeParse parseTool;

        auto statusBitfield = parseTool.getField(std::move(ptr), size);
        std::string newStatus(statusBitfield.first.get(), size);

        this->setStatus(newStatus);

        return std::move(statusBitfield.second);
    }

    void Status::setStatus(eStatusCode const status) noexcept
    {
        this->_status = status;
    }

    void Status::setStatus(std::string const &status) noexcept
    {
        if (this->_statusCode.find(status) != this->_statusCode.end()){
            this->_status = this->_statusCode[status];
        }
        else{
            this->badRequest();
        }
    }
}