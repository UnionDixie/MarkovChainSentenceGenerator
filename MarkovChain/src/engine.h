#include <iostream>
#include <vector>
#include <deque>
#include <map>

#include <cstdlib>
#include <ctime>

#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

//#include "../src/parserArg.h"

//static int cntMalloc = 0;

//void* operator new (size_t size) {
//	cntMalloc++;
//	return malloc(size);
//}

class Engine
{
public:
	Engine(int argc,char**);
	~Engine();
	void run();
	//size_t getCountMalloc();
private:
	//ParserArg parser;
	//void make_pairs(std::vector<std::string>& word);
	std::deque<std::string> word;
	std::map<std::string,int> cntWord;
	std::deque<std::pair<std::string,std::string>> pair;
	std::map<std::string,std::vector<std::string>> dict;
	void createBase();
	void createSentences(int n = 0);
};

Engine::Engine(int argc,char** argv){
	std::cout << "\tEngine Create\n";
	std::srand(std::time(nullptr));
}

Engine::~Engine(){

}

void Engine::createBase() {
	std::cout << "\tHow word in your text?\n";
	int n = 0;
	std::cin >> n;
	std::cout << "\tInput your text\n";
	word.resize(n);

	for (size_t i = 0; i < n; i++)
	{
		std::cin >> word[i];
		cntWord[word[i]]++;
	}
	word.push_front("*start*");
	word.push_back("*end*");

	for (size_t i = 0; i < word.size() - 1; i++)
	{
		pair.push_back({ word[i],word[i + 1] });
		dict[word[i]].push_back(word[i + 1]);
	}
	pair.push_back({ word[word.size() - 1],"*NONE*" });
	dict[word[word.size() - 1]].push_back("*NONE*");

	std::cout << "Create dictonary" << "\n";
	for (const auto& it : dict) {
		std::cout << "\t" << it.first << "\n\t\t";
		for (const auto& it2 : it.second)
			std::cout << it2 << " ";
		std::cout << "\n";
	}
}

void Engine::createSentences(int n) {
	if (n) {
		for (size_t i = 0; i < n; i++)
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(word.begin(), word.end(), std::default_random_engine(seed));//hmmm
			auto start = word[0];
			if (start != "*end*") {
				std::cout << "\n\tSTART\n\t";
				while (find(dict[start].begin(), dict[start].end(), "NONE") == dict[start].end())
				{
					if (start == "*end*")
						break;
					std::cout << start << " ";
					seed = std::chrono::system_clock::now().time_since_epoch().count();
					std::shuffle(dict[start].begin(), dict[start].end(), std::default_random_engine(seed));//hmmm
					if (start == "*NONE*")
						break;
					start = *dict[start].begin();
				}
			}
		}
	}else {
		std::cout << "\n\tEMPTY!!\n";
	}
	return;
}
void Engine::run() {
	createBase();
	std::cout << "How much senctence create?";
	int n;
	std::cin >> n;
	createSentences(n);

	return;
}