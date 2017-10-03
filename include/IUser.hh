//
// Created by florian on 02/10/17.
//

#ifndef EPITECHBABEL_IUSER_HH
#define EPITECHBABEL_IUSER_HH

#include <memory>
#include <set>

#include "IConfig.hh"

namespace User {

    class IUser {
    public:
        using id_type = unsigned int;
        using user_type = std::shared_ptr<IUser>;
        using manager_type = std::set<user_type>;
        using email_type = std::string;
        using name_type = std::string;
        using password_type = std::string;

        virtual ~IUser() {};

        /**
         * Clone IUser instance
         * @return
         */
        virtual std::unique_ptr<IUser> clone() const = 0;
        /**
         * Init user
         * @return
         */
        virtual bool init(IConfig const &) noexcept = 0;
        /**
         * Return name of user
         * @return
         */
        virtual name_type const &getName() const noexcept = 0;
        /**
         * Set name of user
         */
        virtual void setName(name_type const &) noexcept = 0;
        /**
         * Get email of user
         * @return
         */
        virtual email_type const &getEmail() const noexcept = 0;
        /**
         * Set email of user
         */
        virtual void setEmail(email_type const &) noexcept = 0;
        /**
         * Return id of user
         * @return
         */
        virtual id_type getID() const noexcept = 0;
        /**
         * Set id of user if is not set (== 0)
         */
        virtual bool setID(id_type const &) noexcept = 0;
        /**
         * Return the manager
         * @return
         */
        virtual manager_type &getContacts() noexcept = 0;
        virtual manager_type const &getContacts() const noexcept = 0;
        /**
         * Set password of user
         */
        virtual void setPassword(password_type const &) noexcept = 0;
        /**
         * Check if the password is correct.
         * @return
         * @throw if is not same.
         */
        virtual bool isPassword(password_type const &) const = 0;


        bool operator==(const IUser& user) const
        {
            return this->getID() == user.getID();
        }
        bool operator!=(const IUser& user) const
        {
            return this->getID() != user.getID();
        }
    };
}

#endif //EPITECHBABEL_IUSER_HH
