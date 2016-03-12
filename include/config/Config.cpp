#include "Config.hpp"

std::string wg::config::Config::root_path = "";

using namespace wg::config;

void wg::config::Config::setRootPath(std::string args0)
{
	//�܂��A���4�����͕K��.exe�ł��邱�Ƃ��m�F����
	if (args0.substr(args0.length() - 4).compare(".exe") != 0) {
		return;
	}

	//�k���Ă����A\��������/��������
	for (int i = args0.length() - 4; i >= 0; i--) {
		if (args0[i] == '\\' || args0[i] == '/') {
			args0.resize(i + 1);
			break;
		}
	}

	Config::root_path = args0;
}

std::string wg::config::Config::getRootPath(void)
{
	return Config::root_path;
}
