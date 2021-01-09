//#include <iostream>
//#include <string>
//#include <string_view>
//#include <optional>
//#include <vector>
//#include <filesystem>
//#include <sstream>
//#include <fstream>
//#include <memory>
//
//class ParserArg
//{
//public:
//	ParserArg(int argc, char**);
//	std::unique_ptr<std::vector<std::string_view>> getText();
//	~ParserArg();
//private:
//	bool sillentMode = true;
//	void parseArgv(int argc, char** str);
//	std::vector<std::string_view> data;
//	std::vector<std::string_view> word;
//	std::filesystem::path exePath;
//	std::filesystem::path txtPath;
//	std::string tmp;
//	std::ifstream input;
//	std::stringstream sstr;
//};
//
//ParserArg::ParserArg(int argc, char** str) {
//	if (!sillentMode)
//		std::cout << "\tStart parsing...\n";
//	parseArgv(argc, str);
//}
//
//void ParserArg::parseArgv (int argc, char** str) {
//	if (argc)
//		exePath = str[0];
//	for (int i = 0; i < argc; ++i) {
//		data.push_back(str[i]);
//		if(!sillentMode)
//			std::cout << data[i] << " ";
//	}
//
//	if (data.size() < 2) {
//		std::cout << "\tNot found path to file with text\n"
//			      << "\tPlease input path or insert text\n"
//			      << "\t path - \"0 pathToFile \" text - \"1 yourText\"\n";
//		int choose = -1;
//		std::cin >> choose;
//		switch (choose)
//		{
//		case 0:
//			std::cin >> txtPath;
//			input.open(txtPath);
//			while (input >> sstr.rdbuf());
//			tmp = sstr.str();
//			input.close();
//			break;
//		case 1:
//			
//			break;
//		default:
//			break;
//		}
//	}
//	else {
//		for (size_t i = 1; i < data.size(); i++)
//		{
//			input.open(data[i]);
//			while (input >> sstr.rdbuf());
//			tmp += sstr.str()+"\n";
//			input.close();
//		}
//	}
//}
//
//std::unique_ptr<std::vector<std::string_view>> ParserArg::getText() {
//	if (!tmp.empty()) {
//		std::stringstream x;     
//		x << tmp;
//		while (x >> tmp) word.push_back(tmp);
//		std::unique_ptr<std::vector<std::string_view>> res(&word);
//		return res;
//	}
//	else {
//		return nullptr;
//	}
//}
//
//
//
//ParserArg::~ParserArg() {
//	if (!sillentMode)
//		std::cout << "\tDestroy parser\n";
//	exePath.clear();
//	data.clear();
//}