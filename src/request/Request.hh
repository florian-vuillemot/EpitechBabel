#ifndef REQUEST_HH
#define REQUEST_HH

#include <regex>
#include <utility>
#include "../../include/IRequest.hh"
#include "ContainData.hh"

namespace Request{
    class Request : public IRequest
    {
    public:
        using type_response_info = uint32_t;

    public:
        void setHeader(header_type const &) noexcept override ;
        void setRoute(route_type const &) noexcept override ;
        void setData(data_type const &) noexcept override ;
        data_type const & getData() const noexcept override ;
        route_type const & getRoute() const noexcept override ;
        header_type const & getHeader() const noexcept override ;
        bitfield_type serialize() const noexcept override ;
        void load(bitfield_type &&) noexcept override ;

    private:
        template<typename T>
        using container_type = std::unique_ptr<ContainData<T> const>;

        container_type<header_type> header;
        container_type<route_type> route;
        container_type<data_type> data;

        static constexpr type_response_info placeHeader = sizeof(type_response_info) * 3;

    private:
        size_t getRequestSize() const noexcept;
        template <typename T, typename U = T>
        void set(T &toSet, U const &setter) const noexcept ; // Generique setter

        template <typename T, typename TNumPlace, typename TNumSize = TNumPlace>
        bitfield_type loadField(bitfield_type &&bitfield, container_type<T> &toLoad, TNumPlace place, TNumSize size) const noexcept;

        template <typename ParseTool, typename T, typename ...Args>
        void convertFromNetwork(ParseTool const &parseTool, T &first, Args &... args) const noexcept;
        template <typename ParseTool, typename T>
        void convertFromNetwork(ParseTool const &parseTool, T &first) const noexcept;

        type_response_info headerSize() const noexcept;
        type_response_info routeSize() const noexcept;
        type_response_info dataSize() const noexcept;
        type_response_info placeRoute() const noexcept;
        type_response_info placeData() const noexcept;
    };
}

#endif