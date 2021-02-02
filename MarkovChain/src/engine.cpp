//#define NDEBUG

#include "engine.h"

Engine::Engine(std::string_view str,int argc, char** argv):argc(argc),argv(argv) {
	assert(!str.empty() && "Error not correct language");
	print("\tEngine Create\n");
	if (str == l[Language::RU] ) {
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
	read();
}

void Engine::read(){
	word.push_back("*START*");//start point 
	if (argc > 1)//so 1 - path of exe
		readFile();
	else
		readBuffer();
	word.push_back("*END*");//end point 
	print("\tStatitics of word = " + std::to_string(word.size()-2));
	createDict();
}

void Engine::readFile() {
	for (size_t i = 1; i < argc; i++)
	{
		std::ifstream file;
		std::filesystem::path path = argv[i];
		file.open(path);
		if (!file.is_open()) {
			print("\tError to open file path = " + path.string() + "\n");
			print("Call readBuffer - input text\n");
			readBuffer();
		}
		else {
			print("Open file = " + path.string() + "\n");
			std::string input;
			while (file >> input)
			{
				word.push_back(input);
			}
		}
		file.close();
	}
}

void Engine::readBuffer() {
	std::string text;
	print("\tInput your text\n");
	std::getline(std::cin, text);//if text with \0 will be bad!
	std::stringstream buffer(text);
	//parsing...
	while (buffer >> text) {
		word.push_back(text);
	}
}

void Engine::createDict() {
	print("\n\tCreate dictonary\n");
	for (size_t i = 0; i < word.size() - 1; ++i) {
		dict[word[i]].push_back(word[i + 1]);//cat->fish
		wordStatistics[word[i]]++;//optional
	}
	dict[word.back()].push_back("*NONE*");//*END* have next only *NONE*
}

void Engine::run() {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	bool run = true;
	while (run) {
		createSentence();
		print("\n\t1 - run 0 - stop -> ");
		std::cin >> run;
	}
}

void Engine::createSentence() {
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	system("cls");
	print("\tHow much senctence create? -> ");
	int n = 1;
	std::cin >> n;
	print("\tHow max lentgh of sentence -> ");
	int length = 5;
	std::cin >> length;

	if (n > 0) {
		std::mt19937_64 rng;//twister
		for (size_t i = 0; i < n; i++)
		{
			rng.seed(std::chrono::system_clock::now().time_since_epoch().count());//time for seed
			int cnt = 0;//length of sentence
			std::string start = word[rng() % word.size()];//random word
			if (start != "*END*") {
				print("\n\tSTART sentence\n");
				while (find(dict[start].begin(), dict[start].end(), "NONE") == dict[start].end())//only end have none
				{
					print(start + " ");//print new generate word
					++cnt;
					auto seed = std::chrono::system_clock::now().time_since_epoch().count();
					std::shuffle(dict[start].begin(), dict[start].end(), std::default_random_engine(seed));//shuffle vector
					start = *dict[start].begin();
					if (start == "*END*" || cnt == length)
						break;
				}
			}
			else {
				print("\tSorry,empty sentence :(");
			}
		}
	}
	else
		print("\n\tEMPTY INPUT!!!\n");
}

void Engine::print(std::string_view str,bool log){
	if(log)
		std::cout << str;
}

Engine::~Engine() {
	word.clear();
	wordStatistics.clear();
	dict.clear();
	print("\tBye\n");
}
