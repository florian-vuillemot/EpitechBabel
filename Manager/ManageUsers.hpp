/*
** ManageUsers.hpp for EpitechBabel in /home/delrivm/EpitechBabel/Manager/ManageUsers.hpp
**
** Made by Matthieu Delrive
** Login   <matthieu.delrive@epitech.eu>
**
** Started on  Tue Sep 26 14:06:42 2017 Matthieu Delrive
** Last update Tue Sep 26 14:06:42 2017 Matthieu Delrive
*/

#ifndef EPITECHBABEL_MANAGEUSERS_HPP
#define EPITECHBABEL_MANAGEUSERS_HPP

#include "IManagerUsers.hpp"

namespace user {

  class ManageUsers : public IManagerUsers {
  public:
	 bool init(IConfig const &config);

	bool exist(std::string const &email) ;

	 std::shared_ptr<IUser> connect(std::string const &email, std::string const &password);

	std::shared_ptr<IUser> getUser(int id, std::string token);

	ManageUsers();

	~ManageUsers();
  };
}

#endif //EPITECHBABEL_MANAGEUSERS_HPP
