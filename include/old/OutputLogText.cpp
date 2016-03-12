#include "OutputLogText.hpp"

std::ofstream wg::systems::OutputLogtext::file;
std::mutex wg::systems::OutputLogtext::mtx_;

int wg::systems::OutputLogtext::Output(const char * str,const char * from)
{
	std::lock_guard<std::mutex> lock(mtx_);
	file.open(OUTPUT_LOGTEXT_FILENAME, std::ios::app);

	if (file.fail() || file.bad()) {
		std::cout << "OutputLogtext>èoóÕÇ™ãëî€Ç≥ÇÍÇ‹ÇµÇΩ\n";
		return -1;
	}

	if (from == NULL) {
		file << ">" << str << "\n";
		std::cout << ">" << str << "\n";
	}
	else {
		file << from << ">" << str << "\n";
		std::cout << from << ">" << str << "\n";
	}

	file.close();
	return 0;
}

int wg::systems::OutputLogtext::OutputS(const std::string str, const std::string from)
{
#ifdef _DEBUG
	Output(str.c_str(), from.c_str());
#endif
	return 0;
}

int wg::systems::OutputLogtext::OutputS_E(const std::string str, const std::string from)
{
	Output(("[Error]" + str).c_str(), from.c_str());
	return 0;
}

