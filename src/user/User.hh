//
// Created by florian on 03/10/17.
//

#ifndef EPITECHBABEL_USER_HH
#define EPITECHBABEL_USER_HH

#include "../../include/IUser.hh"

namespace User {
    class User : public IUser
    {
    public:
        User();
        ~User();

        std::unique_ptr<IUser> clone() const override ;
        bool init(IConfig const &) noexcept override ;
        name_type const &getName() const noexcept override ;
        void setName(name_type const &) noexcept override ;
        email_type const &getEmail() const noexcept override ;
        void setEmail(email_type const &) noexcept override ;
        id_type getID() const noexcept override ;
        bool setID(id_type const &) noexcept override ;
        manager_type &getContacts() noexcept override ;
        manager_type const &getContacts() const noexcept override ;
        void setPassword(password_type const &) noexcept override ;
        bool isPassword(password_type const &) const override ;
        void setToken(token_type const &) noexcept override ;
        bool isToken(token_type const &) const noexcept override ;
        token_type const &getToken() const noexcept override ;
        IUser::ip_type const &getIp() const noexcept override ;
        void setIp(ip_type const &) noexcept override ;

    private:
        id_type id;
        manager_type contacts;
        name_type name;
        email_type email;
        password_type password;
        token_type token;
        ip_type ip;
    };
}

#endif //EPITECHBABEL_USER_HH
