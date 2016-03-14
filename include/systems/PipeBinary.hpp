#pragma once

#ifndef WG_SYSTEMS_PIPEBINARY_HPP
#define WG_SYSTEMS_PIPEBINARY_HPP

#include <string>
#include <vector>
#include <list>
#include <mutex>

namespace wg {
	namespace systems {
		class PipeBinary {
		public:

			class Data {
			public:
				virtual ~Data();

				Data(const std::string message);
				Data(const unsigned char* data, const std::size_t size);

				std::size_t get(unsigned char * data, const std::size_t allocated_size) const;
				std::string get(void) const;

				bool isString(void) const;

				std::string _Gtf(void) const;
				
			private:
				Data();

				enum _Dtp : unsigned char{
					PIPE_NODATA = 0x00,
					PIPE_STRING_DATA = 0x01,
					PIPE_BINARY_DATA = 0x02,
					PIPE_LONGDATA_END = 0x03
				};

				_Dtp dtype;
				std::vector<unsigned char> data;

			};

			PipeBinary(const std::string pipe_name, const bool is_host, const unsigned int timeout_ms = 0);
			virtual ~PipeBinary(void);

			bool send(const Data & d);

		private:
			PipeBinary(void);
			PipeBinary(const PipeBinary & copy);

			std::mutex mtx;

			std::string filename;
			unsigned int timeout_ms;
			bool is_host;

			std::list<Data> dlist;

			void _Thd(void);

		};
	};
};

#endif //end of WG_SYSTEMS_PIPEBINARY_HPP