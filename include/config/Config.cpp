#include "Config.hpp"

std::string wg::config::Config::root_path = "";

using namespace wg::config;

void wg::config::Config::setRootPath(std::string args0)
{
	//まず、語尾4文字は必ず.exeであることを確認する
	if (args0.substr(args0.length() - 4).compare(".exe") != 0) {
		return;
	}

	//遡っていき、\もしくは/を見つける
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
