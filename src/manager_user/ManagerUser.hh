#ifndef MANAGER_USER_HH
#define MANAGER_USER_HH

#include <set>
#include <vector>
#include <cstdlib>

#include "../../include/IManagerUser.hh"
#include "../user/User.hh"

namespace ManagerUser {

    class ManagerUser : public IManagerUser {
    public:
        bool init(IConfig const &) noexcept override ;
        std::optional<user_type> connect(email_type const &, password_type const &) const noexcept override ;
        std::optional<user_type> get(id_type const) const noexcept override ;
        std::optional<user_type> get(email_type const &) const noexcept override;
        void push(user_type const &user) noexcept override ;
        void push(user_type &&user) noexcept override ;
        std::optional<user_type> getConnect(email_type const &, token_type const &) const noexcept override ;
        void disconnect(id_type const) const noexcept override ;
        std::optional<ip_type> ifConnect(id_type const) const noexcept override ;

    private:
        template <typename FCT>
        std::optional<user_type> find(FCT const fct) const noexcept ;
        void setToken(user_type::element_type &) const noexcept;
        token_type getToken() const noexcept;
        bool tokenExist(token_type const &) const noexcept ;
        token_type findToken() const noexcept;
        auto rand() const noexcept -> decltype(std::rand());
        User::IUser::id_type getId() const noexcept;

    private:
        std::vector<user_type> users;
    };

}
#endif