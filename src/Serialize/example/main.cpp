//
// Created by florian on 28/09/17.
//

#include <iostream>
#include <memory>

#include "../../../include/Serialize.hh"
#include "../../config/BasicConfig/BasicConfig.hh"

int main()
{
    BasicConfig conf;
    Serialize<int> s;
    Serialize<int> s2;

    if (!s.init(conf) || !s2.init(conf)){
        std::cerr << "bad init" << std::endl;
        return 0;
    }
    auto i = std::make_unique<int>(4);
    s.create(1, std::move(i));
    std::cout << s.getSize() << std::endl;
    std::cout << *s.getData() << std::endl;

    s2.create(2, new int(3));
    if (!s2.available())
        std::cout << "Error" << std::endl;

    std::cout << s2.getSize() << std::endl;
    auto ptr = s2.getData();
    std::cout << *ptr << std::endl;

    if (s2.available())
        std::cout << "Error" << std::endl;
    return 0;
}