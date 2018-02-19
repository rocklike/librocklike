#include "gtest/gtest.h"
#include "rl_network_networkmessage.hpp"
#include <cstring>

namespace {

class NetworkMessageTest : public ::testing::Test {
protected:
	void SetUp() {
		this->message.setRequestData(this->testStr, std::strlen(this->testStr));
	}
	const char testStr[15] = "Hello World";
	rocklike::NetworkMessage message;

};

TEST_F(NetworkMessageTest, doSetGetRequestData) {
	ASSERT_STREQ(testStr, message.getRequestData());
	ASSERT_EQ( std::strlen(testStr), message.getRequestDataSize());
}

}
