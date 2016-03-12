
#include <thread>
#include "Network.hpp"
#include "../systems/OutputLogText.hpp"
#include "../systems/INIFileReader.hpp"

std::atomic<int> wg::networks::Network::all_id = 0;

void wg::networks::Network::Connect(){

	this->status_ = -1;
	this->id = all_id;
	all_id++;

	::std::thread network_thread(&Network::NetworkThread, this);
	network_thread.detach();
	
}


sf::Socket::Status wg::networks::Network::readLine(std::vector<std::string> * dst)
{
	char data[2048];
	size_t rec_size;
	sf::Socket::Status st = socket_.receive(data, 2048, rec_size);

	if (rec_size == 2048) wg::systems::OutputLogtext::OutputS_E("バッファがいっぱいです","Network");
	std::string tmp;

	if (st == sf::Socket::Done) {
		for (int i = 0; i < rec_size; i++) {
			if (data[i] == '\n') {
				dst->push_back(tmp);
				tmp.clear();
			}
			if(data[i] != '\r' && data[i] != '\n') tmp.push_back(data[i]);
		}
	}

	return st;
}

void wg::networks::Network::NetworkThread(void) {


	//コネクティングの作業
	sf::Socket::Status status = socket_.connect(this->ipadress_, this->port_);
	if (status != sf::Socket::Done)
	{
		::wg::systems::OutputLogtext::OutputS("サーバーとの接続に失敗しました。IP:" + this->ipadress_ + "\tPORT:" + std::to_string(this->port_), "Network.cpp");
		this->status_ = 0;
		return;
	}

	this->status_ = 1;

	socket_.setBlocking(false);
	//スレッドの立ち上げ

	sf::Packet pk;
	std::string receive;
	size_t rec_size = 0;
	char data[1024];

	while (!this->is_thread_exit_) {

		// TCP socket
		std::vector<std::string> rec;
		sf::Socket::Status rec_stat = this->readLine(&rec);
		if (rec_stat == sf::Socket::Done) {
			for (int i = 0; i < rec.size(); i++) {
				if (rec[i].compare("") == 0) {
					wg::systems::OutputLogtext::OutputS_E("i<改行のみのプロトコル","Network");
				}
				else {
					receive_que_.push_back(rec[i]);
					wg::systems::OutputLogtext::OutputS("i<" + rec[i], "Network");
				}
			}
		}


		// TCP socket
		if (send_que_.size() > 0) {
			for (int i = 0; i < 1024; i++) data[i] = 0;
			std::string str = send_que_.front();
			wg::systems::OutputLogtext::OutputS("o>" + str, "Network");
			str = str + "\r\n";
			if (socket_.send(str.c_str(),str.size(),rec_size) != sf::Socket::Done){
				::wg::systems::OutputLogtext::OutputS("Sendに失敗。またこのエラーは、今後のプログラム製作段階で、適切なエラー処理が要求されます。一時的のエラー処理であることをお忘れなきよう。", "Network.cpp");
			}
			send_que_.pop_front();
		}
		
	}
	
	socket_.disconnect();

	is_thread_exited_ = true;
}

void wg::networks::Network::setDestination(const std::string ipadress, const uint16_t port)
{
	this->ipadress_ = ipadress;
	this->port_ = port;
}


std::vector<std::string> wg::networks::Network::getData(){
	std::lock_guard<std::mutex> lock(this->mtx_);
	std::vector<std::string> ret;

	std::string str = receive_que_.front();


	ret.push_back("");
	for (std::string::const_iterator p = str.begin(); p != str.end(); p++) {
		if (*p == ' ') ret.push_back("");
		else ret[ret.size() - 1].push_back(*p);
	}

	return ret;
}

std::string wg::networks::Network::getData(const size_t index)
{
	std::vector<std::string> args(this->getData());
	if (index < args.size()) {
		return args[index];
	}
	return std::string("");
}

bool wg::networks::Network::equal(const size_t index,const std::string str)
{
	return this->getData(index).compare(str) == 0;
}

std::string wg::networks::Network::operator[](const size_t index)
{
	return this->getData(index);
}

void wg::networks::Network::delete_front(void)
{
	if(receive_que_.size() > 0)	receive_que_.pop_front();
}

size_t wg::networks::Network::getQueNum(void){
	std::lock_guard<std::mutex> lock(this->mtx_);
	if (receive_que_.size() > 0) {
		int n = 0;
	}
	return receive_que_.size();
}

void wg::networks::Network::setListenFlag(const bool f){
	std::lock_guard<std::mutex> lock(this->mtx_);
	is_listen_ = f;
}

bool wg::networks::Network::isListen(void){
	std::lock_guard<std::mutex> lock(this->mtx_);
	return is_listen_;
}

bool wg::networks::Network::isOverflow(){
	std::lock_guard<std::mutex> lock(this->mtx_);
	return is_overflow_;
}

void wg::networks::Network::ClearOverflowFlag(){
	std::lock_guard<std::mutex> lock(this->mtx_);
	is_overflow_ = false;
}

int wg::networks::Network::send(const std::string & data){
	std::lock_guard<std::mutex> lock(this->mtx_);
	send_que_.push_back(data);
	return 0;
}

void wg::networks::Network::Disconnect(){
	std::lock_guard<std::mutex> lock(this->mtx_);
	
	if (this->status_ <= 0) return;


	this->is_thread_exit_ = true;
	while(is_thread_exited_ == false);
}

int wg::networks::Network::getStatus()
{
	std::lock_guard<std::mutex> lock(this->mtx_);
	return this->status_;
}
