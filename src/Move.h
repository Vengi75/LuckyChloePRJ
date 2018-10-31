/*
 * Move.h
 *
 *  Created on: 31 paü 2018
 *      Author: Vengi
 */

#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

class Move
{
  public:
  Move (std::vector<std::string> vec){}

    std::string Command;
    std::string HitLevel; // l,m,h == 1,2,3
    //damage been made into subclass
    std::string OnHit; //remember to do string to int conversion
    std::string OnBlock; //remember to do string to int conversion
    std::string CH_Properties; //CS,KND,Launch, none == 1,2,3,4,

    virtual void whoAmI() = 0;
    virtual int sort() = 0;
    virtual ~Move(){};
};


#endif /* MOVE_H_ */
