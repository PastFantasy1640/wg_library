
#pragma once

#ifndef WG_NETWORKS_NETWORK_HPP
#define WG_NETWORKS_NETWORK_HPP

#include <string>
#include <list>
#include <atomic>
#include <mutex>
#include <SFML/Network.hpp>


namespace wg {
	namespace networks {
		class Network {
		public:

			enum Settings {
				QUEUE_MAXSIZE = 1024
			};

			void Connect();
			::std::vector<std::string> getData();
			std::string getData(const size_t index);
			bool equal(const size_t index, const std::string str);
			std::string operator[](const size_t index);
			void delete_front(void);
			size_t getQueNum(void);
			void setListenFlag(const bool f);
			bool isListen(void);
			bool isOverflow();
			void ClearOverflowFlag();
			int send(const std::string & data);
			void Disconnect();
			int getStatus();



		private:
			::std::list<std::string> receive_que_;
			::std::list<std::string> send_que_;
			::std::mutex mtx_;
			::std::atomic<bool> is_thread_exit_;
			::std::atomic<bool> is_thread_exited_;
			bool is_listen_;
			bool is_overflow_;

			::std::string ipadress_;
			int port_;

			::std::atomic<int> status_;

			sf::Socket::Status readLine(std::vector<std::string> * dst);

			sf::TcpSocket socket_;

			void NetworkThread(void);
			void setDestination(const std::string ipadress, const uint16_t port);

			static std::atomic<int> all_id;
			int id;

		};
	}
}

#endif