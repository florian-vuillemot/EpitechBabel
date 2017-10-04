#include <ctime>
#include <algorithm>
#include "ManagerUser.hh"

namespace ManagerUser {

    bool ManagerUser::init(IConfig const &) noexcept {
        return true;
    }

    std::optional <IManagerUser::user_type> ManagerUser::connect(email_type const &email, password_type const &password) const noexcept {
        auto user = this->find([email, password](User::IUser const &user){
            return user.getEmail() == email and user.isPassword(password);
        });

        if (user and *user){
            this->setToken(**user);
        }

        return user;
    }

    std::optional <IManagerUser::user_type> ManagerUser::get(id_type const id) const noexcept {
        return this->find([id](auto const &user){
            return user.getID() == id;
        });
    }

    std::optional<IManagerUser::user_type> ManagerUser::get(email_type const &email) const noexcept
    {
        return this->find([email](auto const &user){
            return user.getEmail() == email;
        });
    }

    void ManagerUser::push(user_type const &user) noexcept {
        auto const userId = user->getID();

        if (!this->get(userId)){
            auto const id = this->getId();
            user->setID(id);
            this->users.push_back(user);
        }
    }
    void ManagerUser::push(user_type &&user) noexcept {
        auto const userId = user->getID();

        if (!this->get(userId)){
            auto const id = this->getId();
            user->setID(id);
            this->users.push_back(std::move(user));
        }
    }

    template <typename FCT>
    std::optional<IManagerUser::user_type> ManagerUser::find(FCT const fct) const noexcept
    {
        for (auto &user: this->users){
            if (fct(*user)){
                return user;
            }
        }
        return {};
    }

    void ManagerUser::setToken(user_type::element_type &user) const noexcept
    {
        auto token = this->findToken();

        user.setToken(token);
    }

    IManagerUser::token_type ManagerUser::findToken() const noexcept {
        auto const token = this->getToken();

        if (this->tokenExist(token)){
            return this->findToken();
        }
        return std::move(token);
    }

    IManagerUser::token_type ManagerUser::getToken() const noexcept {
        std::string const alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        auto const sizeAlphanum = alphanum.size();

        auto const len = this->rand();
        std::string res;

        for (auto i = 0; i < len; ++i) {
            auto const place = rand() % sizeAlphanum;
            res += alphanum[place];
        }

        return std::move(res);
    }

    bool ManagerUser::tokenExist(token_type const &token) const noexcept {
        auto const exist = this->find([&](auto const &user){
            return user.isToken(token);
        });

        return exist ? true : false;
    }

    auto ManagerUser::rand() const noexcept -> decltype(std::rand()) {
        static auto size = min_size_token;

        size = size > max_size_token ? min_size_token : size;

        std::srand(std::time(0));
        auto const len = std::rand() % max_size_token + size;

        size += 1;

        return len;
    }

    User::IUser::id_type ManagerUser::getId() const noexcept {
        if (0 == this->users.size()) {
            return 1;
        }

        auto const maxUser = std::max_element(this->users.begin(), this->users.end(),
                                [](std::shared_ptr <User::IUser> const &u1,
                                   std::shared_ptr <User::IUser> const &u2) {
                                    return *u1 < *u2;
                                });
        auto const id = maxUser->get()->getID();
        return id + 1;
    }
}