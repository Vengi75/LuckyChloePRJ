//============================================================================
// Name        : LuckyChloePRJ.cpp
// Author      : Jaques van Zyl - Vengi57
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

class Move;
class Damage_Factory;
class factory;

class Move
{

/*
  private:
  PowerCrush ps;
  Homing ps;
  TailSpin ps;
  RageArts ps;
  SpecialMoves ps;
*/

  public:
	 Move (std::vector<std::string> vec)
	  {

	  }

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

class factory
{
 public:
virtual Move *create_Move(const std::vector<std::string> &vec) = 0; //make one for each special class

virtual ~factory(){};
};

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

class Damage_Factory : public factory
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
      return new Damage(vec);
    }
    virtual ~Damage_Factory(){};
};

class PowerCrush : public Move
{
public:
  std::string crushString;
  PowerCrush (const std::vector<std::string> &vec)
  :Move(vec)
    {
    crushString = vec [7];  //correct element of vector goes here - ??
    }

  void whoAmI()
  {
	  std::cout<<"I'm PowerCrush object"<<std::endl;
  }

  virtual int sort(){}
};

class PowerCrush_Factory : public factory //inherit from class.move
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new PowerCrush(vec);
    }
    virtual ~PowerCrush_Factory(){};
};



class Homing : public Move
{
public:
  std::string homeString;
  Homing (const std::vector<std::string> &vec)
  :Move(vec)
    {
    homeString = vec [7];
    }
  void whoAmI()
  {
	  std::cout<<"I'm Homing object"<<std::endl;
  }

  virtual int sort(){}
};

class fullLineData
{
  public:
	fullLineData (const std::vector<std::string> &vec) : moveData{vec}
  {
		Damage_Factory dmgFactory{};
		Move* ptr{dmgFactory.create_Move(moveData)};
		MoveVecPtr.push_back(ptr);
  }

	fullLineData (const fullLineData &data) : moveData{data.moveData},
			MoveVecPtr{data.MoveVecPtr}
	{
	}

	fullLineData& operator=(const fullLineData& data)
	{
		if(this == &data)
			return *this;

		moveData = data.moveData;
		MoveVecPtr = data.MoveVecPtr;
		return *this;
	}


  int sortByDamage()
  {
	  return MoveVecPtr[0]->sort();
  }

	std::vector<std::string> moveData;
	std::vector<Move*> MoveVecPtr;
};


std::ostream& operator << (std::ostream& os, const fullLineData& data)
{
	for( auto & lineElement : data.moveData){
		  os << lineElement << ' ';
	}

	return os;
}

class Homing_Factory : public factory //inherit from class.move
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new Homing(vec);
    }
    virtual ~Homing_Factory(){};
};


class TailSpin : public Move
{
public:
  std::string tailString;
  TailSpin (const std::vector<std::string> &vec)
  :Move(vec)
    {
    tailString = vec [7];
    }

  void whoAmI()
    {
  	  std::cout<<"I'm TailSpin object"<<std::endl;
    }

  virtual int sort(){}
};

class TailSpin_Factory : public factory //inherit from class.move
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new TailSpin(vec);
    }
    virtual ~TailSpin_Factory(){};
};


 // Remember to only generate rageArts objs if Rage vector == 'y'


class RageArt : public Move
{
public:
  std::string rageString;
  RageArt (const std::vector<std::string> &vec)
  :Move(vec)
    {
    rageString = vec [8];
    }
  void whoAmI()
    {
  	  std::cout<<"I'm RageArt object"<<std::endl;
    }

  virtual int sort(){}
};

class RageArt_Factory : public factory //inherit from class.move
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new RageArt(vec);
    }
    virtual ~RageArt_Factory(){};
};

 // Remember to only generate special objs if special vector == 'y'

class specialMove : public Move
{
public:
  std::string specialString;
  specialMove (const std::vector<std::string> &vec)
  :Move(vec)
    {
    specialString = vec [6];
    }

  void whoAmI()
    {
  	  std::cout<<"I'm SpecialMove object"<<std::endl;
    }

  virtual int sort(){}
};

class specialMove_Factory : public factory //inherit from class.move
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new specialMove(vec);
    }
    virtual ~specialMove_Factory(){};
};

void sortByDamage(std::vector<fullLineData>& vectorOfLines)
{
	std::sort(vectorOfLines.begin(),vectorOfLines.end(),[](fullLineData &a, fullLineData &b)->bool{
		return (a.sortByDamage() < b.sortByDamage());
	});

	for(auto line : vectorOfLines)
	{
		std::cout<<line<<std::endl;
	}
}


class CSVReader
{
	std::string fileName;
	char delimeter;

public:
	CSVReader(std::string filename, char delm = ',') :
			fileName{filename}, delimeter{delm}
	{ }

	std::vector<std::vector<std::string> > getData();
};

std::vector<std::vector<std::string> > CSVReader::getData()
{
	std::ifstream file{fileName};

	std::vector<std::vector<std::string> > dataList{};
	std::vector<std::string> vec{};

    if(file.is_open())
    {
    	std::cout<<"file opened!"<<std::endl;

    	std::string line{""};

    	while (getline(file, line))
    	{
    		std::stringstream ss{line};
    	    while(getline(ss, line, delimeter)){
        		vec.push_back(line);
        		line = "";
    	    }
    	}

    	file.close();
    }

    std::cout<<"reading done"<<std::endl;

    int sublinesCounter{0};
    int lineCount{0};
    bool quotes{false};
    std::string quotesString{};
    dataList.push_back(std::vector<std::string>{});

    for(auto lineElement : vec)
    {
    	std::cout<<"sublinesCounter begin: "<<sublinesCounter<<std::endl;
    	std::cout<<"lineElement: "<<lineElement<<std::endl;

    	if((lineElement.front() == '"') && (lineElement.back() != '"'))
    	{
    		std::cout<<"first option"<<std::endl;

    		quotes = true;
    		quotesString.append(lineElement);
    		quotesString.push_back(',');
    	}
    	else if((quotes == true) && (lineElement.back() != '"'))
    	{
    		std::cout<<"second option"<<std::endl;

    		quotesString.append(lineElement);
    		quotesString.push_back(',');
    	}
    	else if(lineElement.back() == '"')
        {
    		std::cout<<"third option"<<std::endl;

    		quotes = false;

    		quotesString.append(lineElement);

        	if(sublinesCounter == 9)
        	{
        		dataList[lineCount].push_back(quotesString);

        		sublinesCounter = 0;
        		++lineCount;
        		dataList.push_back(std::vector<std::string>{});
        	}
        	else
        	{
        		dataList[lineCount].push_back(quotesString);
        		++sublinesCounter;
        	}

        	quotesString.clear();
        }
    	else if(sublinesCounter == 9)
    	{
    		std::cout<<"fourth option"<<std::endl;

    		dataList[lineCount].push_back(lineElement);

    		sublinesCounter = 0;
    		++lineCount;
    		dataList.push_back(std::vector<std::string>{});
    	}
    	else
    	{
    		std::cout<<"fifth option"<<std::endl;

    		dataList[lineCount].push_back(lineElement);
    		++sublinesCounter;
    	}

    	std::cout<<"sublinesCounter end: "<<sublinesCounter<<std::endl;
    	std::cout<<"lineCount end: "<<lineCount<<std::endl;
    }

	dataList.erase(--dataList.end());

    std::ofstream outputFile{"Trace_Output.txt"};
    for(auto lines : dataList)
    {
    	for(auto lineElems : lines)
    	{
   		  outputFile<<lineElems<<' ';
    	}
    	outputFile<<std::endl;
    }
    outputFile.close();

	return dataList;
};




int main()
{
	CSVReader cSVReader{"Character_Data.csv"};

	std::vector<std::vector<std::string> > moveListData {cSVReader.getData()};

	PowerCrush_Factory pcFactory {};

	Move* powerCrushPtr{};

	Homing_Factory hFactory {};

	Move* homingPtr{};

	TailSpin_Factory tsFactory {};

	Move* tailSpinPtr{};

	RageArt_Factory raFactory {};

	Move* ragePtr;

	specialMove_Factory specFactory {};
	Move* specPtr;

	std::vector<fullLineData> vectorOfLines{};
	vectorOfLines.push_back(fullLineData{moveListData[1]});
	vectorOfLines.push_back(fullLineData{moveListData[2]});
	vectorOfLines.push_back(fullLineData{moveListData[3]});
	vectorOfLines.push_back(fullLineData{moveListData[4]});
	vectorOfLines.push_back(fullLineData{moveListData[5]});

	sortByDamage(vectorOfLines);


for(auto & singleLine : moveListData)
	{
    	if(singleLine[8] == "Power crush")
		{
			powerCrushPtr = pcFactory.create_Move(singleLine);
			std::cout<<powerCrushPtr<<std::endl;
		}
	}

	if(powerCrushPtr != nullptr)
	{
	  powerCrushPtr->whoAmI();
	}
	delete powerCrushPtr;

for(auto & singleLine : moveListData)
		{
		  if(singleLine[8] == "Homing")
			{
				homingPtr = hFactory.create_Move(singleLine);
				std::cout<<homingPtr<<std::endl;
			}

	  }

		if(homingPtr != nullptr)
		{
		  homingPtr->whoAmI();
		}
		delete homingPtr;

for(auto & singleLine : moveListData)
			{
			  if(singleLine[8] == "Tail spin")
				{
					tailSpinPtr = tsFactory.create_Move(singleLine);
					std::cout<<tailSpinPtr<<std::endl;
				}
		    }

			if(tailSpinPtr != nullptr)
			{
			  tailSpinPtr->whoAmI();
			}
			delete tailSpinPtr;

for (auto & singleLine : moveListData)
  {
    if (singleLine [9] == "y")
    {
    	ragePtr = raFactory.create_Move(singleLine);
    	std::cout<<ragePtr<<std::endl;
    }
    else
    {
    	//make base class move
    }

    if(ragePtr != nullptr)
    	{
    	  ragePtr->whoAmI();
    	}
    	delete ragePtr;
  }

for (auto & singleLine : moveListData)
  {
    if (singleLine [6] == "y")
    {
    	specPtr = specFactory.create_Move(singleLine);
    	std::cout<<specPtr<<std::endl;
    }
    else
    {
    	//make base class move
    }

    if(specPtr != nullptr)
    	{
    	  specPtr->whoAmI();
    	}
    	delete ragePtr;
  }

    std::getchar();
    return 0;
}
