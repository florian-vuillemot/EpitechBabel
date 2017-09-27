#include <fstream>
#include <iostream>
#include "BasicConfig.hh"

bool BasicConfig::init(std::string const &filename) noexcept
{
    return this->loadFile(filename);
}

bool BasicConfig::exist(std::string const &label, std::string const &key) const noexcept {
    if (this->configs.find(label) != this->configs.end()){
        auto const &category = this->configs.at(label);

        return category.find(key) != category.end();
    }

    return false;
}

std::string const & BasicConfig::get(std::string const &label, std::string const &key) const
{
    return this->configs.at(label).at(key);
}


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

bool BasicConfig::loadFile(std::string const &filename) noexcept  {
    std::ifstream file;

    if (file.open(filename.c_str()); file.is_open()){
        auto success = this->parseFile(file);

        file.close();
        return success;
    }

    return false;
}

bool BasicConfig::parseFile(std::ifstream &file) noexcept {
    std::string line, label;

    while (std::getline(file, line)){
        if (!line.empty()) {
            if (this->isLabel(line)) {
                label = std::move(this->getLabel(line));

                this->addLabel(label);
            }
            else {
                auto const delim = this->posChar(line, BasicConfig::configDelim);
                auto const canLoad = delim && !label.empty();

                if (!canLoad || !this->recordKeyValue(line, *delim, this->configs.at(label))){
                    return false;
                }
            }
        }
    }
    return true;
}

bool BasicConfig::addLabel(std::string const &label) noexcept {
    decltype(this->configs)::mapped_type newConfig;
    decltype(this->configs)::value_type conf(label, newConfig);

    return this->addConfig(this->configs, label, std::move(conf));
}

template <typename T, typename U, typename N>
bool BasicConfig::addConfig(std::map<T, U> &container, std::string const &label, N &&ctor) const noexcept {
    if (container.find(label) == container.end()){
        auto const res = container.insert(ctor);

        return res.second;
    }

    return false;
}

bool BasicConfig::isLabel(std::string const &line) const noexcept {
    return line.back() == BasicConfig::labelDelim &&
            !this->posChar(line, BasicConfig::configDelim) &&
            line.size() > 1;
}

std::string BasicConfig::getLabel(std::string const &line) const noexcept {
    return line.substr(0, line.size() - 1);
}

bool BasicConfig::recordKeyValue(std::string const &line, size_t const pos,
                                 std::map<std::string, std::string> &container) const noexcept
{
    auto const key = line.substr(0, pos);
    auto const value = line.substr(pos + 1);
    auto newConfig = std::make_pair(key, value);

    if (this->addConfig(container, key, std::move(newConfig))) {
        container.at(key) = value;
        return true;
    }

    return false;
}

std::optional<size_t> BasicConfig::posChar(std::string const &str, char const search, size_t cursor) const noexcept {
    auto const pos = str.find(search, cursor);

    if (pos != std::string::npos && pos > 0){
        if ('\\' == str.at(pos - 1)){
            return this->posChar(str, search, cursor + pos);
        }

        return pos;
    }

    return {};
}
