#ifndef FRAMEWORK_RL_NETWORK_NETWORKMESSAGE_HPP_
#define FRAMEWORK_RL_NETWORK_NETWORKMESSAGE_HPP_

#include <string>
#include <exception>
#include <iostream>

#include "rl_sendio_exception.hpp"
#include "rl_connection_stub.hpp"

namespace rocklike
{

class RL_TCPConnection;

class NetworkMessage
{
  public:
  	NetworkMessage();
	NetworkMessage(const NetworkMessage & other);
	NetworkMessage(NetworkMessage && other);
	~NetworkMessage();

	NetworkMessage& operator=(NetworkMessage && other);
	NetworkMessage& operator=(const NetworkMessage & other);

	const static size_t MAX_MSG_LEN = 1024;

	void setRequestData(const char *src, const std::size_t dataLen);
	const char *getRequestData() const;

	const std::size_t getRequestDataSize() const;

	void setResponseData(const char *src, const std::size_t dataLen);
	const char *getResponseData() const;

	const std::size_t getResponseDataSize() const;

	void setSourceConnection(std::shared_ptr<ConnectionStub> connStubPtr);

	std::shared_ptr<ConnectionStub> connStubPtr_;

	int connUseCount();

  private:
	char * requestData_;
	std::size_t requestDataSize_;

	char * responseData_;
	std::size_t responseDataSize_;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_NETWORK_NETWORKMESSAGE_HPP_ */
