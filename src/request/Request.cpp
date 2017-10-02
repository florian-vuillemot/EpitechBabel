#include "Request.hh"
#include "SerializeParse.hh"

namespace Request
{
    void Request::setHeader(header_type const &header) noexcept
    {
        this->set(this->header, header);
    }

    void Request::setRoute(route_type const &route) noexcept
    {
        this->set(this->route, route);
    }

    void Request::setData(data_type const &data) noexcept
    {
        this->set(this->data, data);
    }

    IRequest::bitfield_type Request::serialize() const noexcept
    {
        Serialize::SerializeParse const parseTool;

        auto const requestSize = this->getRequestSize();
        auto bitfield = bitfield_type(new bitfield_type::element_type[requestSize]);

        auto header = parseTool.toBitField(this->header->getStr(), this->headerSize());
        auto route = parseTool.toBitField(this->route->getStr(), this->routeSize());
        auto data = parseTool.toBitField(this->data->getStr(), this->dataSize());

        bitfield = parseTool.serialize(std::move(bitfield),
                                       parseTool.convertForNetwork(this->headerSize()),
                                       parseTool.convertForNetwork(this->routeSize()),
                                       parseTool.convertForNetwork(this->dataSize()));

        bitfield = parseTool.setField(std::move(bitfield), std::move(header), this->headerSize(), this->placeHeader).first;
        bitfield = parseTool.setField(std::move(bitfield), std::move(route), this->routeSize(), this->placeRoute()).first;
        bitfield = parseTool.setField(std::move(bitfield), std::move(data), this->dataSize(), this->placeData()).first;

        return std::move(bitfield);
    }

    void Request::load(bitfield_type &&serializer) noexcept
    {
        Serialize::SerializeParse const parseTool;
        type_response_info sizeHeader, sizeRoute, sizeData;

        serializer = parseTool.load(std::move(serializer), sizeHeader, sizeRoute, sizeData);
        this->convertFromNetwork(parseTool, sizeHeader, sizeRoute, sizeData);

        serializer = this->loadField(std::move(serializer), this->header, this->placeHeader, sizeHeader);
        serializer = this->loadField(std::move(serializer), this->route, this->placeRoute(), sizeRoute);
        serializer = this->loadField(std::move(serializer), this->data, this->placeData(), sizeData);
    }


    IRequest::data_type const &Request::getData() const noexcept
    {
        return this->data->getData();
    }
    IRequest::route_type const &Request::getRoute() const noexcept
    {
        return this->route->getData();
    }
    IRequest::header_type const &Request::getHeader() const noexcept
    {
        return this->header->getData();
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    ///////////////////////////////////////////

    template <typename T, typename U = T>
    void Request::set(T &toSet, U const &setter) const noexcept
    {
        using template_element_type = typename T::element_type;

        toSet = std::unique_ptr<template_element_type const>(new template_element_type(setter));
    }

    template <typename T, typename TNumPlace, typename TNumSize = TNumPlace>
    IRequest::bitfield_type Request::loadField(bitfield_type &&bitfield, container_type<T> &toLoad, TNumPlace place, TNumSize size) const noexcept
    {
        Serialize::SerializeParse const parseTool;

        auto newfield = parseTool.getField(std::move(bitfield), size, place);
        std::string const res(newfield.first.get(), size);
        this->set(toLoad, res);

        return std::move(newfield.second);
    }

    template <typename ParseTool, typename T, typename ...Args>
    void Request::convertFromNetwork(ParseTool const &parseTool, T &first, Args &... args) const noexcept
    {
        this->convertFromNetwork(parseTool, first);
        this->convertFromNetwork(parseTool, args...);
    }

    template <typename ParseTool, typename T>
    void Request::convertFromNetwork(ParseTool const &parseTool, T &toConvert) const noexcept
    {
        toConvert = parseTool.convertFromNetwork(toConvert);
    }

    size_t Request::getRequestSize() const noexcept {
        return this->headerSize() + this->routeSize() + this->dataSize() + this->placeHeader;
    }

    Request::type_response_info Request::headerSize() const noexcept{
        return this->header->getStr().size();
    }
    Request::type_response_info Request::routeSize() const noexcept{
        return this->route->getStr().size();
    }
    Request::type_response_info Request::dataSize() const noexcept{
        return this->data->getStr().size();
    }

    Request::type_response_info Request::placeRoute() const noexcept{
        return this->headerSize() + this->placeHeader;
    }

    Request::type_response_info Request::placeData() const noexcept{
        return this->placeRoute() + this->routeSize();
    }
}