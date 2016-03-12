#pragma once

#ifndef JOE_CONFIG_HPP
#define JOE_CONFIG_HPP

#include <string>

namespace wg {
	namespace config {
		class Config {
		private:
			static std::string root_path;
		public:
			static void setRootPath(std::string args0);
			static std::string getRootPath(void);
		};
	};
};

#endif