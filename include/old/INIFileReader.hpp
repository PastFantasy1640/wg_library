#pragma once

#ifndef WG_SYSTEMS_INI_FILEREADER_H_
#define WG_SYSTEMS_INI_FILEREADER_H_

#include <string>
#include <fstream>
#include <vector>

namespace wg {
	namespace systems {
		struct INIFileReaderElements {
			std::string section_;
			std::string key_;
			std::string value_;
		};

		class INIFileReader {
		public:

			INIFileReader(const std::string filename);

			int LoadFile(const std::string filename);
			int ReloadFile();

			std::string getValue(const std::string section, const std::string key, const std::string def_str = "") const;
			int RewriteValue(const std::string section, const std::string key, std::string value);

			void Delete();

			~INIFileReader() {}

		private:
			INIFileReader();
			//unsigned int element_num_;

			std::vector<INIFileReaderElements>data_;

			std::fstream file_;

			std::string filename_;

			bool is_load_;


		};
	}
}


#endif
