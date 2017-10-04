//
// Created by florian on 03/10/17.
//

#include "User.hh"

namespace User {
    User::User(){
        this->id = 0;
        this->ip = "";
        this->token = "";
    }
    User::~User(){
    }

    std::unique_ptr<User::IUser> User::clone() const{
        return std::unique_ptr<User>(new User);
    }

    bool User::init(IConfig const &) noexcept {
        return true;
    }

    IUser::name_type const &User::getName() const noexcept {
        return this->name;
    }

    void User::setName(name_type const &name) noexcept {
        this->name = name;
    }

    IUser::email_type const &User::getEmail() const noexcept {
        return this->email;
    }

    void User::setEmail(email_type const &email) noexcept {
        this->email = email;
    }

    IUser::id_type User::getID() const noexcept {
        return this->id;
    }

    bool User::setID(id_type const &id) noexcept {
        if (0 == this->id){
            this->id = id;
            return true;
        }
        return false;
    }

    IUser::manager_type &User::getContacts() noexcept {
        return this->contacts;
    }

    IUser::manager_type const &User::getContacts() const noexcept{
        return this->contacts;
    }

    void User::setPassword(password_type const &password) noexcept {
        this->password = password;
    }

    bool User::isPassword(password_type const &password) const {
        return this->password == password;
    }

    void User::setToken(token_type const &token) noexcept {
        this->token = token;
    }

    bool User::isToken(token_type const &token) const noexcept {
        return this->token == token;
    }

    IUser::token_type const &User::getToken() const noexcept {
        return this->token;
    }

    IUser::ip_type const &User::getIp() const noexcept {
        return this->ip;
    }

    void User::setIp(ip_type const &ip) noexcept {
        this->ip = ip;
    }
}