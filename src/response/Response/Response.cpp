//
// Created by florian on 28/09/17.
//

#include <utility>
#include "Response.hh"
#include <iostream>
namespace Response {
    bool Response::load(serialize_type &&serialize) noexcept {
        using _serialize_data = std::pair<serialize_type::typeSize, serialize_type::typePtr>;

        ResponseInfo infosResponse;
        _serialize_data ptrData(serialize.getSize(), serialize.getData());

        ptrData.second = this->getResponseInfo(std::move(ptrData.second), infosResponse);
        
    }

    bool Response::serialize(serialize_type &) const noexcept {

    }

    void Response::setStatus(status_type const &) noexcept {

    }

    void Response::setData(std::string const &) noexcept {

    }

    IResponse::serialize_type::typePtr Response::getResponseInfo(serialize_type::typePtr &&ptr, ResponseInfo &rp) const noexcept
    {
        SerializeParse const parseTool;

        return parseTool.load(std::move(ptr), rp.endian, rp.statusSize, rp.dataSize);
    }
}
