#include "engine.h"

Engine::Engine(int argc, char** argv):argc(argc),argv(argv) {
	std::cout << "\tEngine Create\n";
	if (1) {
		//setlocale(LC_ALL, "Russian");
		//setlocale(LC_CTYPE, "rus");
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
	if (argc > 1)
		readFile();
	else 
		readBuffer();
	createDict();
}

void Engine::run() {
	bool run = true;
	while (run) {
		createSentences();
		std::cin >> run;//1 -> run
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
	}
}

void Engine::readFile() {
	for (size_t i = 1; i < argc; i++)
	{
		std::ifstream file;
		std::filesystem::path path = argv[i];
		file.open(path);
		if (!file.is_open())
			std::cout << "Error to open file path = " << path.string()<<"\n";
		else {
			std::cout << "Open file = " << path.string()<<"\n";
			std::string input;
			word.push_back("*START*");//start point 
			while (file >> input)
			{
				word.push_back(input);
			}
			word.push_back("*END*");//start point 
		}
		file.close();
	}
}


void Engine::readBuffer() {
	std::string text;
	std::cout << "\tInput your text\n";
	std::getline(std::cin, text);
	std::stringstream buffer(text);
	//parsing...
	word.push_back("*START*");//start point 
	while (buffer >> text) {
		word.push_back(text);
	}
	word.push_back("*END*");//and end point of sentences
}

void Engine::createDict() {
	//create dict
	std::cout << "Create dictonary" << "\n";
	for (size_t i = 0; i < word.size() - 1; ++i) {
		dict[word[i]].push_back(word[i + 1]);
		wordStatistics[word[i]]++;//for fan
	}
	dict[word.back()].push_back("*NONE*");//*END* have next only *NONE*
	/*for (const auto& it : dict) { //cout dictonary
		std::cout << "\t" << it.first << "\n\t\t";
		for (const auto& it2 : it.second)
			std::cout << it2 << " ";
		std::cout << "\n";
	}*/
}

void Engine::createSentences() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	system("cls");//clean screen ->cmd
	std::cout << "How much senctence create? -> ";
	int n = 1;
	std::cin >> n;

	if (n>0) {
		std::mt19937_64 rng;//twister
		for (size_t i = 0; i < n; i++)
		{
			rng.seed(std::chrono::system_clock::now().time_since_epoch().count());//random start

			auto posStart = rng() % wordStatistics.size();//0..size();
			std::string start = "*END*";
			for (auto it = wordStatistics.begin(); it!=wordStatistics.end(); ++it) {
				if (posStart-1 == std::distance(wordStatistics.begin(), it)) {
					start = it->first;
				}
			}
			if (start != "*END*") {
				std::cout << "\n\tSTART sentences\n";
				while (find(dict[start].begin(), dict[start].end(), "NONE") == dict[start].end())//only end have none
				{
					std::cout << start << " ";
					auto seed = std::chrono::system_clock::now().time_since_epoch().count();
					std::shuffle(dict[start].begin(), dict[start].end(), std::default_random_engine(seed));//shuffle vector
					if (start == "*END*" || start == "*NONE*")
						break;
					start = *dict[start].begin();
				}
			}
			else {
				std::cout << "\t\nSorry,empty string :(\n";
			}

		}
	}
	else 
		std::cout << "\n\tEMPTY INPUT!!!\n";
}

Engine::~Engine() {
	word.clear();
	wordStatistics.clear();
	dict.clear();
}
