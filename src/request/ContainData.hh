//
// Created by florian on 02/10/17.
//

#ifndef EPITECHBABEL_CONTAINDATA_HH
#define EPITECHBABEL_CONTAINDATA_HH

#include "Request.hh"

namespace Request {

    static constexpr char delim_field_data = ',';
    static constexpr char delim_key_value_field = ':';

    
    template<typename T>
    class ContainData {
    public:
        ContainData(T const &d) : data(d), str(this->toString(d)) {}
        ContainData(std::string const &dStr) : data(this->toMap(dStr)), str(dStr) {}
        ~ContainData() = default;

        T const &getData() const noexcept {return this->data;}
        std::string const &getStr() const noexcept {return this->str;}

    private:
        T toMap(std::string const &dStr) noexcept {
            T res;
            auto tokens = this->getTokens(dStr, Request::delim_field_data);

            for (auto const &token: tokens) {
                auto splitToken = this->getTokens(token, Request::delim_key_value_field);

                if (2 <= splitToken.size()) {
                    auto const tokenKey = splitToken[0];
                    auto const tokenValue = this->getToken(token, '"');
                    auto const tokenAvailable = std::make_pair(tokenKey, tokenValue);

                    res.insert(tokenAvailable);
                }
            }

            return res;
        }

        std::string toString(T const &d) const noexcept {
            std::string res = "";
            auto prec = false;

            for (auto const &it: d) {
                if (prec) {
                    res += Request::delim_field_data;
                }
                res += it.first + Request::delim_key_value_field + "\"" + it.second + "\"";
                prec = true;
            }

            return res;
        }

        std::vector <std::string> getTokens(std::string const &str, char const search) const noexcept {
            std::vector <std::string> res;

            for (size_t cursor = 0; cursor < str.size(); ++cursor) {
                res.push_back(getToken(str, search, cursor));
            }

            return std::move(res);
        }

        template<typename IT>
        bool cmpInhibitor(std::string const &str, char const delim, IT const &it) const noexcept {
            if (it < str.end()) {
                if (*it != delim) {
                    return true;
                }
                return *(it - 1) == '\\';
            }
            return false;
        };

        std::string getToken(std::string const &str, char const delim) const noexcept {
            std::string res;
            auto it = str.begin();

            while (this->cmpInhibitor(str, delim, it)) {
                ++it;
            }

            if (it < str.end()) {
                for (++it; this->cmpInhibitor(str, delim, it); ++it) {
                    res.push_back(*it);
                }
            }

            return std::move(res);
        }

        std::string getToken(std::string const &str, char const delim, size_t &cursor) const noexcept {
            std::string res;

            for (auto it = str.begin() + cursor; this->cmpInhibitor(str, delim, it); ++it, ++cursor) {
                res.push_back(*it);
            }

            return std::move(res);
        }

    private:
        T const data;
        std::string const str;

    };

    template<>
    class ContainData<std::string> {
    public:
        ContainData(std::string const &dStr) : str(dStr) {}
        ~ContainData() {}

        std::string const &getData() const noexcept {return this->str;}
        std::string const &getStr() const noexcept {return this->str;}

    private:
        std::string const str;
    };
}
#endif //EPITECHBABEL_CONTAINDATA_HH
