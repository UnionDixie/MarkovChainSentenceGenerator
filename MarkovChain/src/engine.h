#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>

#include <sstream>
#include <fstream>

#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <thread>

#include <filesystem>

#include<stdio.h>
#include<windows.h>
#include <clocale>

class Engine
{
public:
	Engine(int argc,char**);
	~Engine();
	void run();
	//size_t getCountMalloc();
private:
	int argc = 0;
	char** argv = nullptr;
	
	void readFile(); 
	void readBuffer();
	void createDict();
	void createSentences();

	std::vector<std::string> word;
	std::map<std::string, int> wordStatistics;
	std::map<std::string, std::vector<std::string>> dict;
};




