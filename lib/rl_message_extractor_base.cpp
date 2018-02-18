#include <memory>

#include "rl_networkmessage_extractor_base.hpp"

namespace rocklike {

MessageExtractorBase::MessageExtractorBase() : readDataSize_(0), sendDataSize_(0) {

}

MessageExtractorBase::~MessageExtractorBase() {

}

char * MessageExtractorBase::readData() {
	return this->readData_;
}

std::size_t MessageExtractorBase::readDataSize() {
	return this->readDataSize_;
}

char * MessageExtractorBase::sendData() {
	return this->sendData_;
}

std::size_t MessageExtractorBase::sendDataSize() {
	return this->sendDataSize_;
}

std::queue<NetworkMessage>& MessageExtractorBase::messagesQueue() {
	return this->messagesQueue_;
}

//int MessageExtractorBase::extract() {
//
//}

}
