/*
** AManager.hpp for EpitechBabel in /home/delrivm/EpitechBabel/Manager/AManager.hpp
**
** Made by Matthieu Delrive
** Login   <matthieu.delrive@epitech.eu>
**
** Started on  Tue Sep 26 13:25:06 2017 Matthieu Delrive
** Last update Tue Sep 26 13:25:08 2017 Matthieu Delrive
*/


#ifndef EPITECHBABEL_AMANAGER_HPP
#define EPITECHBABEL_AMANAGER_HPP


#include <vector>
#include <algorithm>
#include <set>

namespace manager {
  template<typename T>
  class AManager {
  public:
	bool add(T toAdd){
	  return elements.insert(toAdd).second;
	}

	bool remove(T toRemove){
	  if (std::find_if(elements.begin(), elements.end(), [&](auto const &elem){return cmp(elem, toRemove);}) != elements.end()) {
		elements.erase(toRemove);
		return true;
	  }

	  return false;

	}

	std::vector<T> const &get() const{
	  return elements;
	}

	bool exist(T search) {
	  return std::find(elements.begin(), elements.end(), [&](auto const &elem) { return cmp(elem, search); }) != elements.end();
	}


	virtual int cmp(T const &elem1, T const &elem2) const = 0;

  private:
	std::vector<T> elements;
  };

};

#endif //EPITECHBABEL_AMANAGER_HPP
