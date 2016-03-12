#pragma once

#ifndef WG_SYSTEMS_LOGGER_HPP
#define WG_SYSTEMS_LOGGER_HPP

#ifdef _DEBUG
#pragma comment( lib, "LoggerLib_d.lib")
#else
#pragma comment( lib, "LoggerLib.lib")
#endif

#include <fstream>
#include <chrono>
#include <mutex>

#define WG_SYSTEM_LOGGER_DEFAULT_PATH "Logger.ini"

namespace wg {
	namespace systems {

		/// <summary>���O�o�͂��s��static�N���X</summary>
		class Logger {
		public:

			/// <summary>�L�^���郍�O�̃��x��</summary>
			enum LogLevel : unsigned char {
				/// <summary>���ׂẴ��O���o�͂���</summary>
				ALL,
				/// <summary>�x���A����уG���[�̃��O���o�͂���</summary>
				WARNING_AND_ERROR,
				/// <summary>�G���[�̂݃��O���o�͂���</summary>
				ERROR_ONLY
			};

			/// <summary>���O���x����ݒ肷��</summary>
			/// <param name='new_log_level'>�ݒ肷�郍�O���x��</param>
			static void setLogLevel(const LogLevel new_log_level);

			/// <summary>��񃌃x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void information(const std::string text);

			/// <summary>�x�����x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void warning(const std::string text);

			/// <summary>�G���[���x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void error(const std::string text);

			/// <summary>��񃌃x���̃��O���o�͂���</summary>
			/// <param name='text'>�o�͂���e�L�X�g</param>
			static void setOutputStdO(const bool new_value);

		private:
			static std::ofstream _fst;
			static LogLevel _llv;
			static std::mutex _mtx;
			static std::chrono::time_point<std::chrono::system_clock> _stc;
			static bool _sdo;
			static bool _fir;
			Logger();
			~Logger();
			static void _Write(const std::string text);
		};	
	};
};

#endif