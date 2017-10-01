//
// Created by florian on 28/09/17.
//

#include <utility>
#include "Response.hh"
#include "SerializeParse.hh"

namespace Response {
    bool Response::load(serialize_type &&serialize) noexcept
    {
        using _serialize_data = std::pair<serialize_type::type_size, serialize_type::type_ptr>;

        _serialize_data ptrData(serialize.getSize(), serialize.getData());

        if (ptrData.first >= decltype(this->infos)::size){
            ptrData.second = this->setResponseInfo(std::move(ptrData.second), this->infos);

            if (ptrData.first >= this->infos.getSizeBody()){
                this->body.data.clear();
                this->setResponseBody(std::move(ptrData.second), this->infos, this->body);
                return true;
            }
        }

        return false;
    }

    serialize_type Response::serialize() const noexcept
    {
        serialize_type serialize;

        serialize.create(this->infos.getSizeResponse(), new char[this->infos.getSizeResponse()]);
        auto reponseInfo = this->getResponseInfo(std::move(serialize.getData()), this->infos);
        auto response = this->getResponseBody(std::move(reponseInfo), this->infos, this->body);

        serialize.create(this->infos.getSizeResponse(), std::move(response));

        return serialize;
    }

    void Response::setStatus(status_type &&statusCode) noexcept
    {
        this->body.statusCode = std::move(statusCode);
        this->infos.statusSize = this->body.statusCode->status().size();
    }

    void Response::setData(data_type const &data) noexcept
    {
        this->body.data = data;
        this->infos.dataSize = this->body.data.size();
    }

    Response::status_type::element_type const &Response::getStatus() const noexcept
    {
        return *this->body.statusCode.get();
    }

    Response::data_type const &Response::getData() const noexcept
    {
        return this->body.data;
    }


    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////

    serialize_type::type_ptr Response::getResponseInfo(serialize_type::type_ptr &&ptr, ResponseInfo const &rp) const noexcept
    {
        Serialize::SerializeParse const parseTool;

        auto const statusSize = parseTool.convertForNetwork(rp.statusSize);
        auto const dataSize = parseTool.convertForNetwork(rp.dataSize);

        return parseTool.serialize(std::move(ptr), statusSize, dataSize);
    }

    serialize_type::type_ptr Response::setResponseInfo(serialize_type::type_ptr &&ptr, ResponseInfo &rp) const noexcept
    {
        Serialize::SerializeParse const parseTool;

        decltype(rp.statusSize) statusSize;
        decltype(rp.dataSize) dataSize;

        auto res = parseTool.load(std::move(ptr), statusSize, dataSize);

        rp.statusSize = parseTool.convertFromNetwork(statusSize);
        rp.dataSize = parseTool.convertFromNetwork(dataSize);

        return std::move(res);
    }

    serialize_type::type_ptr Response::getResponseBody(serialize_type::type_ptr &&ptr, ResponseInfo const &responseInfo, ResponseBody const &body) const noexcept
    {
        Serialize::SerializeParse const parseTool;

        auto dataField = parseTool.toBitField(body.data, body.data.size());
        auto statusField = body.statusCode->serialize();

        auto statusBitfield = parseTool.setField(std::move(ptr), std::move(statusField), responseInfo.statusSize, responseInfo.getPlaceStatus());
        auto dataBitfield = parseTool.setField(std::move(statusBitfield.first), std::move(dataField), responseInfo.dataSize, responseInfo.getPlaceData());

        return std::move(dataBitfield.first);
    }

    serialize_type::type_ptr Response::setResponseBody(serialize_type::type_ptr &&ptr, ResponseInfo const &responseInfo, ResponseBody &rp) const noexcept
    {
        Serialize::SerializeParse const parseTool;

        auto status = parseTool.getField(std::move(ptr), responseInfo.statusSize, responseInfo.getPlaceStatus());
        auto data = parseTool.getField(std::move(status.second), responseInfo.dataSize, responseInfo.getPlaceData());

        rp.statusCode->load(std::move(status.first), responseInfo.statusSize);
        rp.data.append(data.first.get(), responseInfo.dataSize);

        return std::move(data.second);
    }

    auto Response::ResponseInfo::getSizeResponse() const noexcept -> decltype(ResponseInfo::statusSize + ResponseInfo::dataSize + ResponseInfo::size)
    {
        return this->statusSize + this->dataSize + ResponseInfo::size;
    }

    auto Response::ResponseInfo::getPlaceStatus() const noexcept -> decltype(ResponseInfo::size)
    {
        return Response::ResponseInfo::size;
    }

    auto Response::ResponseInfo::getPlaceData() const noexcept -> decltype(ResponseInfo::statusSize + ResponseInfo::size)
    {
        return this->getPlaceStatus() + this->statusSize;
    }

    auto Response::ResponseInfo::getSizeBody() const noexcept -> decltype(ResponseInfo::statusSize + ResponseInfo::dataSize)
    {
        return this->statusSize + this->dataSize;
    }
}
