#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string_view>
#include <sstream>
#include <fstream>
#include <algorithm>    
#include <array>        
#include <random>       
#include <chrono>     
#include <thread>
#include <filesystem>//readFile
#include <windows.h>//ru - 1251
#include <cassert>

class Engine
{
public:
	Engine(std::string_view,int argc,char**);
	~Engine();
	void run();
private:
	int argc = 0;
	char** argv = nullptr;
	void read();
	void readFile(); 
	void readBuffer();
	void createDict();
	void createSentence();
	void print(std::string_view,bool log = true);
	std::vector<std::string> word;
	std::map<std::string, int> wordStatistics;
	std::map<std::string, std::vector<std::string>> dict;

	//Options
	std::map<int, std::string> l { {0,"eng"}, {1,"ru"} };
	enum Language {
		ENG,
		RU
	};

};




