//
// Created by florian on 02/10/17.
//
#include <iostream>
#include "Manager.hh"

int main()
{
    Manager::Manager<int> m;

    m.push(2);
    m.push(3);
    m.push(2);
    m.push(2);
    m.push(2);

    std::cout << "print2: " << *m.get(2) << std::endl;

    if (m.exist(1)){
        std::cout << "error" << std::endl;
    }

    if (!m.exist(2)){
        std::cout << "error" << std::endl;
    }

    for (auto i: m.get()){
        std::cout << i << std::endl;
    }

    std::cout << "----------------" << std::endl;

    m.remove(1);
    m.remove(2);

    for (auto i: m.get()){
        std::cout << i << std::endl;
    }


    return 0;
}