#include "rl_network_networkmessage.hpp"

namespace rocklike {



void NetworkMessage::setRequestData(const char * src, const std::size_t dataLen) {
	memcpy(this->requestData, src, dataLen);
	this->requestData[dataLen] = '\0';
	this->requestDataSize = dataLen;
}


const char * NetworkMessage::getRequestData() {
	return this->requestData;
}


//void NetworkMessage::setRequestDataSize(const std::size_t size) {
//
//}


const std::size_t NetworkMessage::getRequestDataSize() {
	return this->requestDataSize;
}


void NetworkMessage::setResponseData(const char * src, const std::size_t dataLen) {
	memcpy(this->responseData_, src, dataLen);
	this->responseData_[dataLen] = '\0';
	this->responseDataSize = dataLen;
}


const char * NetworkMessage::getResponseData() {
	return this->responseData_;
}


//void NetworkMessage::setResponseDataSize(const std::size_t size) {
//	this->responseDataSize = size;
//}


const std::size_t NetworkMessage::getResponseDataSize() {
	return this->responseDataSize;
}

void NetworkMessage::setSourceConnection(std::shared_ptr<ConnectionStub> connStubPtr) {
	this->connStubPtr_ = connStubPtr;
}



} // end namespace rocklike


