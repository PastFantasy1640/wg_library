#include <systems/PipeBinary.hpp>

// Data�f�X�g���N�^
// + public method
wg::systems::PipeBinary::Data::~Data()
{
}

// Data�R���X�g���N�^
// + public method
// ������̃f�[�^���i�[����
wg::systems::PipeBinary::Data::Data(const std::string message) : Data()
{
	this->dtype = PIPE_STRING_DATA;
	for (std::string::const_iterator p = message.begin(); p != message.end(); p++) this->data.push_back(static_cast<unsigned char>(*p));
}

// Data�R���X�g���N�^
// + public method
// unsigned char�^�̃f�[�^���i�[����
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
// �f�[�^��unsigned char�^�z��Ɋi�[����B
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
// �f�[�^�𕶎���Ƃ��ĕԂ��B�������ł�������ɋ����ϊ�����
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
// �f�[�^�𕶎��Ƃ��ĔF���ł���ꍇ��true��Ԃ�
bool wg::systems::PipeBinary::Data::isString(void) const
{
	return (this->dtype == PIPE_STRING_DATA);
}

std::string wg::systems::PipeBinary::Data::_Gtf(void) const
{
	std::string ret;
	std::size_t s = 0;
	//[Type][Length][DATA]
		//�������f�[�^��255�o�C�g�����傫���Ƃ�
	for (std::vector<unsigned char>::const_iterator p = this->data.begin(); p != this->data.end();) {
		//�c��o�C�g��
		unsigned int left_byte = this->data.size() - s;
		ret.push_back(static_cast<char>(left_byte & 0x0000ff));

		for (int i = 0; p != this->data.end() && i < 256; i++, p++, s++) {
			ret.push_back(*p);
		}
	}

	if (this->data.size() > 255) {
		//�f�[�^��S�����΂���
		ret.push_back(PIPE_LONGDATA_END);
		ret.push_back(0);
	}

	return ret;
}

// Data�R���X�g���N�^
// - private method
wg::systems::PipeBinary::Data::Data() : dtype(PIPE_NODATA)
{
}
