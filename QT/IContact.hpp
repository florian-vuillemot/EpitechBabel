/*
** IContact.hpp for EpitechBabel in /home/delrivm/EpitechBabel/IContact.hpp
**
** Made by Matthieu Delrive
** Login   <matthieu.delrive@epitech.eu>
**
** Started on  Tue Sep 26 09:18:42 2017 Matthieu Delrive
** Last update Tue Sep 26 09:18:42 2017 Matthieu Delrive
*/



#ifndef EPITECHBABEL_ICONTACT_HPP
#define EPITECHBABEL_ICONTACT_HPP

#include <string>

class IContact {
public:
  bool init(/*IConfig const &config,*/ std::string const &name);
  std::string const &  getName() const;
  int getIp() const;
};


#endif //EPITECHBABEL_ICONTACT_HPP
