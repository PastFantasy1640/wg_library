#pragma once

#ifndef WG_SYSTEM_OUTPUT_LOGTEXT_H
#define WG_SYSTEM_OUTPUT_LOGTEXT_H

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

namespace wg {
	namespace systems {
#define OUTPUT_LOGTEXT_FILENAME "DebugLog.txt"

		class OutputLogtext {
		private:

			static std::ofstream file;
			static std::mutex mtx_;

			static int Output(const char* str, const char * from = NULL);
		public:

			static int OutputS(const std::string str, const std::string from = "");
			static int OutputS_E(const std::string str, const std::string from = "");

		};
	}
}

#endif