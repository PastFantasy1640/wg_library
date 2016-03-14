#include <systems/PipeBinary.hpp>

// Dataデストラクタ
// + public method
wg::systems::PipeBinary::Data::~Data()
{
}

// Dataコンストラクタ
// + public method
// 文字列のデータを格納する
wg::systems::PipeBinary::Data::Data(const std::string message) : Data()
{
	this->dtype = PIPE_STRING_DATA;
	for (std::string::const_iterator p = message.begin(); p != message.end(); p++) this->data.push_back(static_cast<unsigned char>(*p));
}

// Dataコンストラクタ
// + public method
// unsigned char型のデータを格納する
wg::systems::PipeBinary::Data::Data(const unsigned char * data, const std::size_t size) : Data()
{
	if (data == nullptr) {
		this->dtype = PIPE_LONGDATA_END;
	}
	else {

		this->dtype = PIPE_BINARY_DATA;
		for (std::size_t i = 0; i < size;i++)
			this->data.push_back(data[i]);
	}
}

// get
// + public method
// データをunsigned char型配列に格納する。
std::size_t wg::systems::PipeBinary::Data::get(unsigned char * data, const std::size_t allocated_size) const
{
	std::size_t s = 0;
	for (std::vector<unsigned char>::const_iterator p = this->data.begin(); p != this->data.end() && s < allocated_size; p++, s++) {
		data[s] = *p;
	}
	return s;
}

// get
// + public method
// データを文字列として返す。何が何でも文字列に強制変換する
std::string wg::systems::PipeBinary::Data::get(void) const
{
	std::string ret;
	for (std::vector<unsigned char>::const_iterator p = this->data.begin(); p != this->data.end(); p++) {
		ret.push_back(static_cast<char>(*p));
	}
	return ret;
}

// isString
// + public method
// データを文字として認識できる場合にtrueを返す
bool wg::systems::PipeBinary::Data::isString(void) const
{
	return (this->dtype == PIPE_STRING_DATA);
}

std::string wg::systems::PipeBinary::Data::_Gtf(void) const
{
	std::string ret;
	std::size_t s = 0;
	//[Type][Length][DATA]
		//もしもデータが255バイトよりも大きいとき
	for (std::vector<unsigned char>::const_iterator p = this->data.begin(); p != this->data.end();) {
		//残りバイト数
		unsigned int left_byte = this->data.size() - s;
		ret.push_back(static_cast<char>(left_byte & 0x0000ff));

		for (int i = 0; p != this->data.end() && i < 256; i++, p++, s++) {
			ret.push_back(*p);
		}
	}

	if (this->data.size() > 255) {
		//データを全部さばいた
		ret.push_back(PIPE_LONGDATA_END);
		ret.push_back(0);
	}

	return ret;
}

// Dataコンストラクタ
// - private method
wg::systems::PipeBinary::Data::Data() : dtype(PIPE_NODATA)
{
}
