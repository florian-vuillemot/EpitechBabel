//
// Created by florian on 27/09/17.
//

#include <iostream>
#include "BasicConfig.hh"

int main()
{
    auto conf = BasicConfig();

    if (conf.init("testfile"))
    {
        if (conf.exist("label", "key")) {
            std::cout << conf.get("label", "key") << "." << std::endl;
        }

        if (conf.exist("label", "key2")) {
            std::cout << conf.get("label", "key2") << std::endl;
        }

        if (conf.exist("label", "key3")) {
            std::cout << conf.get("label", "key3") << std::endl;
        }



        if (conf.exist("label2", "key")) {
            std::cout << conf.get("label2", "key") << std::endl;
        }

        if (conf.exist("label2", "key2")) {
            std::cout << conf.get("label2", "key2") << std::endl;
        }

        if (conf.exist("label2", "key3")) {
            std::cout << conf.get("label2", "key3") << std::endl;
        }

        if (conf.exist("label2", "lol\\=cou")) {
            std::cout << conf.get("label2", "lol\\=cou") << std::endl;
        }

        if (!conf.exist("label2fd", "lol\\=cou")) {
            std::cout << "ok" << std::endl;
        }
    }
    else{
        std::cout << "bad file" << std::endl;
    }

    return 0;
}