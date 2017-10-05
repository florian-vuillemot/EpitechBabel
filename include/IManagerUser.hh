//
// Created by florian on 03/10/17.
//

#ifndef EPITECHBABEL_IMANAGERUSER_HH
#define EPITECHBABEL_IMANAGERUSER_HH

#include <memory>
#include <optional>

#include "IUser.hh"
#include "IConfig.hh"

namespace ManagerUser
{
    class IManagerUser
    {
    public:
        using user_type = User::IUser::user_type;
        using password_type = User::IUser::password_type;
        using email_type = User::IUser::email_type;
        using id_type = User::IUser::id_type;
        using token_type = User::IUser::token_type;
        using ip_type = User::IUser::ip_type;

        static constexpr int min_size_token = 21;
        static constexpr int max_size_token = 42;

    public:
        /**
         * Init Manager user
         * @return
         */
        virtual bool init(IConfig const &) noexcept = 0;
        /**
         * Return the user with this identity and token.
         * @return
         */
        virtual std::optional<user_type> connect(email_type const &, password_type const &) const noexcept = 0;
        /**
         * Return the user if it connect.
         * @return
         */
        virtual std::optional<user_type> getConnect(email_type const &, token_type const &) const noexcept = 0;
        /**
         * Disconnect the user
         */
        virtual void disconnect(id_type const) const noexcept = 0;
        /**
         * Get the user with id.
         * @return
         */
        virtual std::optional<user_type> get(id_type const) const noexcept = 0;
        /**
         * Return the user ip if connect
         * @return
         */
        virtual std::optional<ip_type> ifConnect(id_type const) const noexcept = 0;
        /**
         * Get user by email
         * @return
         */
        virtual std::optional<user_type> get(email_type const &) const noexcept = 0;
        /**
         * Add user
         * @param user
         */
        virtual void push(user_type const &user) noexcept = 0;
        virtual void push(user_type &&user) noexcept = 0;
    };
}

#endif //EPITECHBABEL_IMANAGERUSER_HH
