/*
** IGUI.hpp for EpitechBabel in /home/delrivm/EpitechBabel/IGUI.hpp
**
** Made by Matthieu Delrive
** Login   <matthieu.delrive@epitech.eu>
**
** Started on  Tue Sep 26 08:56:25 2017 Matthieu Delrive
** Last update Tue Sep 26 08:56:25 2017 Matthieu Delrive
*/


#ifndef EPITECHBABEL_IGUI_HPP
#define EPITECHBABEL_IGUI_HPP


#include <functional>
#include <string>
#include <memory>
#include <vector>
#include "IContact.hpp"

class IGUI {
public:
  bool init(Iconfig const &config);
  bool displayConnection();
  bool displayContacts(std::vector<std::unique_ptr<IContact>> const &contacts);
  bool displayCall(std::unique_ptr<IContact> contact);
  bool displayStopCall();
  bool displaySomeoneCall(std::unique_ptr<IContact> caller);
  bool setConnection(std::function<bool (std::string const &email, std::string const &pass)> cb);
  void setCreator(std::function<bool (std::string const &, std::string const &)> cb);
  void setCall(std::function<bool (std::unique_ptr<IContact>)> cb);
  void setStop(std::function<bool ()> cb);
  void setExit(std::function<bool ()> cb);
  void setHangUp(std::function<bool (bool)> cb);
};


#endif //EPITECHBABEL_IGUI_HPP
