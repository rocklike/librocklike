#ifndef FRAMEWORK_RL_NETWORKMESSAGE_EXTRACTOR_BASE_HPP_
#define FRAMEWORK_RL_NETWORKMESSAGE_EXTRACTOR_BASE_HPP_

#include <cstdlib>
#include <queue>

#include "rl_network_networkmessage.hpp"

namespace rocklike {

enum ExtractResult {
	EXTRACT_ERROR = -2,
	DECODE_ERROR = -1,
	SUCCESS_CONTINUE = 0,
	SUCCESSS_STOP = 1
};

class MessageExtractorBase {
public:
	MessageExtractorBase();
	virtual ~MessageExtractorBase();
	virtual int extract(char *data, const std::size_t dataSize, std::size_t & remainingDataSize) = 0;
	virtual NetworkMessage && decode(char *data, size_t len) = 0;
	static const std::size_t BUFF_MAX_LEN = 1024;

	char * readData();
	std::size_t readDataSize();

	char * sendData();
	std::size_t sendDataSize();

	std::queue<NetworkMessage>& messagesQueue();


private:
	char readData_[BUFF_MAX_LEN];
	std::size_t readDataSize_;

	char sendData_[BUFF_MAX_LEN];
	std::size_t sendDataSize_;

	std::queue<NetworkMessage> messagesQueue_;

};

}


#endif /* FRAMEWORK_RL_NETWORKMESSAGE_EXTRACTOR_BASE_HPP_ */
