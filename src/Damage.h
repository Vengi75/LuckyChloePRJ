/*
 * Damage.h
 *
 *  Created on: 31 paü 2018
 *      Author: Vengi
 */

#ifndef DAMAGE_H_
#define DAMAGE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

class Damage : public Move
{
public:
  int dmgString;
  Damage (const std::vector<std::string> &vec)
  :Move(vec)
    {
    dmgString = std::stoi(vec[3]);  //correct element of vector goes here - ??
    }

  void whoAmI()
  {
	  std::cout<<"I'm Damage object"<<std::endl;
  }

  virtual int sort()
  {
	  return dmgString;
  }
};

#endif /* DAMAGE_H_ */
