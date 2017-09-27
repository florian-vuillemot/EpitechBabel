#ifndef BASIC_CONFIG_HH
#define BASIC_CONFIG_HH

#include <map>
#include <optional>
#include "../../../include/IConfig.hh"

class BasicConfig: public IConfig
{
public:
    bool init(std::string const &filename) noexcept override ;
    bool exist(std::string const &label, std::string const &key) const noexcept override ;
    std::string const & get(std::string const &label, std::string const &key) const override ;

public:
    char labelDelim = ':';
    char configDelim = '=';

private:
    // Add element in container at key if not exist.
    template <typename T, typename U, typename N>
    bool addConfig(std::map<T, U> &container, std::string const &key, N &&element) const noexcept;
    bool recordKeyValue(std::string const &line, size_t const pos, std::map<std::string, std::string> &) const noexcept;

    // Gestion file.
    bool loadFile(std::string const &) noexcept;
    bool parseFile(std::ifstream &file) noexcept;

    // Label operations
    bool isLabel(std::string const &line) const noexcept;
    std::string getLabel(std::string const &line) const noexcept;
    bool addLabel(std::string const &label) noexcept;

    // Get optional position of a char in string.
    std::optional<size_t> posChar(std::string const &, char const, size_t cursor = 0) const noexcept ;

private:
    std::map<std::string, std::map<std::string, std::string>> configs;
};


#endif