#include "rl_network_message.hpp"

namespace rocklike
{

NetworkMessage::NetworkMessage() : 
	requestData_(nullptr), responseData_(nullptr), 
	requestDataSize_(0), responseDataSize_(0)
{
}

NetworkMessage::NetworkMessage(const NetworkMessage & other) :
	NetworkMessage()
{
	std::cout << "Copy Assignment" << std::endl;
	this->connStubPtr_ = other.connStubPtr_;
	if (other.getRequestData() != nullptr && other.getRequestDataSize() > 0) 
	{
		this->setRequestData(other.getRequestData(), other.getRequestDataSize());
	}
	if (other.getResponseData() != nullptr && other.getResponseDataSize() > 0)
	{
		this->setResponseData(other.getResponseData(), other.getResponseDataSize());
	}
}

NetworkMessage::NetworkMessage(NetworkMessage && other) :
	NetworkMessage()
{
	std::cout << "Move Constructor" << std::endl;
	this->connStubPtr_ = other.connStubPtr_;
	this->requestData_ = other.requestData_;
	this->responseData_ = other.responseData_;
	this->requestDataSize_ = other.requestDataSize_;
	this->responseDataSize_ = other.responseDataSize_;

	other.connStubPtr_.reset();
	other.requestData_ = nullptr;
	other.responseData_ = nullptr;
	other.requestDataSize_ = 0;
	other.responseDataSize_ = 0;
}

NetworkMessage::~NetworkMessage()
{
	std::cout << "Destroying NetworkMessage: " << this->connStubPtr_.use_count() << std::endl;
	if (this->requestData_ != nullptr) {
		delete this->requestData_;
		this->requestData_ = nullptr;
	}
	if (this->responseData_ != nullptr) {
		delete this->responseData_;
		this->responseData_ = nullptr;
	}
}

NetworkMessage& NetworkMessage::operator=(NetworkMessage && other) 
{
	std::cout << "Move Assignment" << std::endl;
	this->connStubPtr_ = other.connStubPtr_;
	this->requestData_ = other.requestData_;
	this->responseData_ = other.responseData_;
	this->requestDataSize_ = other.requestDataSize_;
	this->responseDataSize_ = other.responseDataSize_;

	other.connStubPtr_.reset();
	other.requestData_ = nullptr;
	other.responseData_ = nullptr;
	other.requestDataSize_ = 0;
	other.responseDataSize_ = 0;

	return *this;

}

NetworkMessage& NetworkMessage::operator=(const NetworkMessage & other) 
{
	std::cout << "Copy Assignment" << std::endl;
	this->connStubPtr_ = other.connStubPtr_;

	this->setRequestData(other.getRequestData(), other.getRequestDataSize());
	this->setResponseData(other.getResponseData(), other.getResponseDataSize());

	return *this;

}

void NetworkMessage::setRequestData(const char *src, const std::size_t dataLen)
{
	if (dataLen > MAX_MSG_LEN || dataLen == 0) {
		throw std::length_error("NetworkMessage::setRequestData DatadataLen is > MAX_MSG_LEN or 0");
	}
	if (src == nullptr) {
		throw std::invalid_argument("NetworkMessage::setRequestData src is null");
	}
	if (this->requestData_ == nullptr) {
		this->requestData_ = new char[MAX_MSG_LEN+2];
	}

	memcpy(this->requestData_, src, dataLen);
	this->requestData_[dataLen] = '\0';
	this->requestDataSize_ = dataLen;
}

const char *NetworkMessage::getRequestData() const
{
	return this->requestData_;
}

const std::size_t NetworkMessage::getRequestDataSize() const
{
	return this->requestDataSize_;
}

void NetworkMessage::setResponseData(const char *src, const std::size_t dataLen)
{
	if (dataLen > MAX_MSG_LEN || dataLen == 0) {
		throw std::length_error("NetworkMessage::setRequestData DatadataLen is > MAX_MSG_LEN or 0");
	}
	if (src == nullptr) {
		throw std::invalid_argument("NetworkMessage::setRequestData src is null");
	}
	if (this->responseData_ == nullptr) {
		this->responseData_ = new char[MAX_MSG_LEN+2];
	}
	memcpy(this->responseData_, src, dataLen);
	this->responseData_[dataLen] = '\0';
	this->responseDataSize_ = dataLen;
}

const char *NetworkMessage::getResponseData() const
{
	return this->responseData_;
}

const std::size_t NetworkMessage::getResponseDataSize() const
{
	return this->responseDataSize_;
}

void NetworkMessage::setSourceConnection(std::shared_ptr<ConnectionStub> connStubPtr)
{
	this->connStubPtr_ = connStubPtr;
}

int NetworkMessage::connUseCount()
{
	return this->connStubPtr_.use_count();
}

} // end namespace rocklike
