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
}

int main()
{
	CSVReader cSVReader{"Character_Data.csv"};

	cSVReader.getData();

    std::getchar();
    return 0;
}
