//
// Created by florian on 03/10/17.
//

#include <memory>
#include <iostream>

#include "../user/User.hh"
#include "ManagerUser.hh"

int main()
{
    ManagerUser::ManagerUser m;;

    auto val = std::shared_ptr<User::IUser>(new User::User);
    val->setEmail("Antony");
    val->setPassword("pass");

    auto val2 = std::shared_ptr<User::IUser>(new User::User);
    val2->setEmail("Flop");
    val2->setPassword("pass");

    m.push(std::move(val));
    m.push(std::move(val2));

    auto antony = m.connect("Antony", "pass");
    if (antony){
        std::cout << (*antony)->getEmail() << " " << (*antony)->getToken() << std::endl;
    }

    auto flop = m.connect("Flop", "pass");
    if (flop){
        std::cout << (*flop)->getEmail() << " " << (*flop)->getToken() << std::endl;
    }


    return 0;
}