/*
** IManager.hpp for EpitechBabel in /home/delrivm/EpitechBabel/Manager/IManager.hpp
**
** Made by Matthieu Delrive
** Login   <matthieu.delrive@epitech.eu>
**
** Started on  Tue Sep 26 13:25:02 2017 Matthieu Delrive
** Last update Tue Sep 26 13:25:02 2017 Matthieu Delrive
*/



#ifndef EPITECHBABEL_IMANAGER_HPP
#define EPITECHBABEL_IMANAGER_HPP


#include <memory>
#include "AManager.hpp"

class IUser{

};

class IConfig{

};

namespace user {
	class IManagerUsers : public manager::AManager<IUser> {
	public:
	  virtual bool init(IConfig const &config) = 0;

	  virtual bool exist(std::string const &email) = 0;

	  virtual std::shared_ptr<IUser> connect(std::string const &email, std::string const &password) = 0;

	  virtual std::shared_ptr<IUser> getUser(int id, std::string token) = 0;

	  virtual ~IManagerUsers() {};
	};
};

#endif //EPITECHBABEL_IMANAGER_HPP
