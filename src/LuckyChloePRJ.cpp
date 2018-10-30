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
   std::string Damage; //remember to do string to int conversion
   std::string OnHit; //remember to do string to int conversion
   std::string OnBlock; //remember to do string to int conversion
   std::string CH_Properties; //CS,KND,Launch, none == 1,2,3,4,

   virtual void whoAmI() = 0;

   virtual ~Move(){};
};

class factory
{
 public:
virtual Move *create_Move(const std::vector<std::string> &vec) = 0; //make one for each special class

virtual ~factory(){};
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
};

class PowerCrush_Factory : public factory //inherit from class.move
{
  public:
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new PowerCrush(vec); //remember to add forward declarations
    }
    virtual ~PowerCrush_Factory(){};
};


/*
class Homing : public Move
{
  std::string homeString;
  Homing (std::vector<std::string> &vec)
  :Move(vec)
    {
    std::vector<std::string> vec (7);  //correct element of vector goes here - ??
    }
};

class Homing_Factory : public factory //inherit from class.move
{
  public: move;
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new Homing(vec); //remember to add forward declarations
    }
    virtual ~Homing_Factory();
};


class TailSpin : public Move
{
  std::string tailString;
  TailSpin (std::vector<std::string> &vec)
  :Move(vec)
    {
    std::vector<std::string> vec (7);  //correct element of vector goes here - ??
    }
};

class TailSpin_Factory : public factory //inherit from class.move
{
  public: move;
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new TailSpin(vec); //remember to add forward declarations
    }
    virtual ~TailSpin_Factory();
};


 * Remember to only generate rageArts objs if Rage vector == 'y'
*/
/*
class RageArt : public Move
{
  std::string rageString;
  RageArt (std::vector<std::string> &vec)
  :Move(vec)
    {
    std::vector<std::string> vec (8);  //correct element of vector goes here - ??
    }
};

class RageArt_Factory : public factory //inherit from class.move
{
  public: move;
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new RageArt(vec); //remember to add forward declarations
    }
    virtual ~RageArt_Factory();
};
*/
/*
 * Remember to only generate special objs if special vector == 'y'
*/
/*
class specialMove : public Move
{
  std::string specialString;
  specialMove (std::vector<std::string> &vec)
  :Move(vec)
    {
    std::vector<std::string> vec (6);  //correct element of vector goes here - ??
    }
};

class specialMove_Factory : public factory //inherit from class.move
{
  public: move;
    virtual Move *create_Move(const std::vector<std::string> &vec)
    {
    return new specialMove(vec); //remember to add forward declarations
    }
    virtual ~specialMove_Factory();
};*/

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

    std::getchar();
    return 0;
}
