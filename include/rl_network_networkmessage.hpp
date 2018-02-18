#ifndef FRAMEWORK_RL_NETWORK_NETWORKMESSAGE_HPP_
#define FRAMEWORK_RL_NETWORK_NETWORKMESSAGE_HPP_

#include <string>
#include <exception>
#include <iostream>

#include "rl_sendio_exception.hpp"
#include "rl_connection_stub.hpp"

namespace rocklike {

class RL_TCPConnection;

class NetworkMessage {
public:

//	NetworkMessage(const NetworkMessage& a)
//	{
//		this->setRequestData();
//		this->setRes`
//		m_ptr = new T;
//		*m_ptr = *a.m_ptr;
//	}

	const static size_t MSGLEN = 1024;

	void setRequestData(const char * src, const std::size_t dataLen);
	const char * getRequestData();

//	void setRequestDataSize(const std::size_t size);
	const std::size_t getRequestDataSize();

	void setResponseData(const char * src, const std::size_t dataLen);
	const char * getResponseData();

//	void setResponseDataSize(const std::size_t size);
	const std::size_t getResponseDataSize();

	void setSourceConnection(std::shared_ptr<ConnectionStub> connStubPtr);

	std::shared_ptr<ConnectionStub> connStubPtr_;

private:
	char requestData[MSGLEN+1];
	std::size_t requestDataSize;

	char responseData_[MSGLEN+1];
	std::size_t responseDataSize;


};

} // end namespace rocklike

#endif /* FRAMEWORK_RL_NETWORK_NETWORKMESSAGE_HPP_ */
