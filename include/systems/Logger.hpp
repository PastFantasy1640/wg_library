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

		/// <summary>ログ出力を行うstaticクラス</summary>
		class Logger {
		public:

			/// <summary>記録するログのレベル</summary>
			enum LogLevel : unsigned char {
				/// <summary>すべてのログを出力する</summary>
				ALL,
				/// <summary>警告、およびエラーのログを出力する</summary>
				WARNING_AND_ERROR,
				/// <summary>エラーのみログを出力する</summary>
				ERROR_ONLY
			};

			/// <summary>ログレベルを設定する</summary>
			/// <param name='new_log_level'>設定するログレベル</param>
			static void setLogLevel(const LogLevel new_log_level);

			/// <summary>情報レベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void information(const std::string text);

			/// <summary>警告レベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void warning(const std::string text);

			/// <summary>エラーレベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
			static void error(const std::string text);

			/// <summary>情報レベルのログを出力する</summary>
			/// <param name='text'>出力するテキスト</param>
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