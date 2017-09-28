//
// Created by florian on 27/09/17.
//

#include <iostream>
#include <string>
#include "../CircularBuffer.hh"
#include "../../../config/BasicConfig/BasicConfig.hh"

int main()
{
    BasicConfig conf;
    if (!conf.init("testfile")){
        std::cout << "fail init config" << std::endl;
        return 0;
    }
    CircularBuffer<std::string> c;
    if (!c.init(conf)){
        std::cout << "fail init" << std::endl;
        return 0;
    }
    for (auto i = 0; i < 20; ++i){
        std::string str = "";
        str += std::to_string(i);
        c.put(std::move(str));
        if (i > 4 && i % 5 == 0){
            if (!c.canGet()){
                std::cout << "error0" << std::endl;
            }
            std::cout << c.get() << std::endl;
            if (!c.canGet()){
                std::cout << "error1" << std::endl;
            }
            std::cout << c.get() << std::endl;
            if (!c.canGet()){
                std::cout << "error2" << std::endl;
            }
            std::cout << c.get() << std::endl;
            std::cout << c.get() << std::endl;
            std::cout << c.get() << std::endl;
            if (c.canGet()){
                std::cout << "error3" << std::endl;
            }
        }
    }

    for (auto i = 0; i < 5; ++i){
        std::string str = "";
        str += std::to_string(i);
        c.put(std::move(str));
    }
    std::cout << c.get() << std::endl;
    std::cout << c.get() << std::endl;
    std::cout << c.get() << std::endl;
    std::cout << c.get() << std::endl;
    std::cout << c.get() << std::endl;

    std::string str = "100";
    c.put(std::move(str));
    std::cout << "after move: " << c.get() << std::endl;

    while (c.canGet())
        std::cout << c.get() << std::endl;

    return 0;
}