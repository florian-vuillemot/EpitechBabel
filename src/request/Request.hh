#ifndef REQUEST_HH
#define REQUEST_HH

#include <regex>
#include <utility>
#include "../../include/IRequest.hh"

namespace Request{
    class Request : public IRequest
    {
    public:
        using type_response_info = uint32_t;
        static constexpr char delim_field_data = ',';
        static constexpr char delim_key_value_field = ':';

    public:
        void setHeader(header_type const &) noexcept override ;
        void setRoute(route_type const &) noexcept override ;
        void setData(data_type const &) noexcept override ;
        bitfield_type serialize() const noexcept override ;
        void load(bitfield_type &&) noexcept override ;

    private:
        template <typename T>
        struct ContainData
        {
            T const data;
            std::string const str;

            ContainData(T const &d): data(d), str(this->toString(d)){}
            ContainData(std::string const &dStr): data(this->toMap(dStr)), str(dStr){}
            ~ContainData() = default;

            T toMap(std::string const &dStr) noexcept
            {
                T res;
                auto tokens = this->getTokens(dStr, Request::delim_field_data);

                for (auto const &token: tokens){
                    auto splitToken = this->getTokens(token, Request::delim_key_value_field);
                    if (2 == splitToken.size()){
                        auto toInsert = std::make_pair(splitToken[0], splitToken[1]);

                        res.insert(std::move(toInsert));
                    }
                }

                return res;
            }

            std::string toString(T const &d) const noexcept
            {
                std::string res = "";
                auto prec = false;

                for (auto const &it: d){
                    if (prec){
                        res += Request::delim_field_data;
                    }
                    res += it.first + Request::delim_field_data + "\"" + it.second + "\"";
                    prec = true;
                }

                return res;
            }

            std::vector<std::string> getTokens(std::string const &str, char const search) const noexcept
            {
                std::vector<std::string> res;

                for (size_t cursor = 0; cursor < str.size(); ++cursor){
                    res.push_back(getToken(str, search, cursor));
                }

                return std::move(res);
            }

            std::string getToken(std::string const &str, char const delim, size_t cursor) const noexcept {
                std::string res;

                auto const cmp = [&](auto const &it){
                    if (it < str.end()){
                        if (*it != delim || it == str.begin()){
                            return true;
                        }
                        return *(it - 1) == '\\';
                    }
                    return false;
                };

                for (auto it = str.begin() + cursor; cmp(it); ++it){
                    res.push_back(*it);
                }

                return std::move(res);
            }
        };

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