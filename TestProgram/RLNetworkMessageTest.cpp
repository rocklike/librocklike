#include "gtest/gtest.h"
#include "rl_network_message.hpp"
#include <cstring>
#include <boost/asio.hpp>
#include "rl_tcpconnection.hpp"

namespace
{

class NetworkMessageTest : public ::testing::Test
{
  protected:
	void SetUp()
	{
		this->cStrReqTDLen = strlen(cStrReqTD);
		this->msgSourceTD.setRequestData(this->cStrReqTD, this->cStrReqTDLen);

		this->cStrRespTDLen = strlen(cStrRespTD);
		this->msgSourceTD.setResponseData(this->cStrRespTD, this->cStrRespTDLen);

		this->newConnectionPtr = rocklike::RL_TCPConnection::create(this->io_context);

		ASSERT_EQ(1, this->newConnectionPtr.use_count());

		this->msgSourceTD.setSourceConnection(this->newConnectionPtr);

		ASSERT_EQ(2, this->newConnectionPtr.use_count());
		ASSERT_EQ(2, msgSourceTD.connUseCount());
	}

	char cStrReqTD[50] = "Request Data";
	std::size_t cStrReqTDLen;

	char cStrRespTD[50] = "Response Data";
	std::size_t cStrRespTDLen;

	rocklike::NetworkMessage msgSourceTD;

	std::shared_ptr<rocklike::RL_TCPConnection> newConnectionPtr;

	boost::asio::io_context io_context;
};

TEST_F(NetworkMessageTest, newConstruct)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_EQ(nullptr, netMsg.getRequestData());
	ASSERT_EQ(0, netMsg.getRequestDataSize());

	ASSERT_EQ(nullptr, netMsg.getResponseData());
	ASSERT_EQ(0, netMsg.getResponseDataSize());

	ASSERT_EQ(nullptr, netMsg.connStubPtr_.get());

	ASSERT_EQ(0, netMsg.connUseCount());
}

TEST_F(NetworkMessageTest, setReqeustData)
{
	rocklike::NetworkMessage netMsg;
	netMsg.setRequestData(cStrReqTD, cStrReqTDLen);

	ASSERT_STREQ(cStrReqTD, netMsg.getRequestData());
	ASSERT_EQ(cStrReqTDLen, netMsg.getRequestDataSize());
}

TEST_F(NetworkMessageTest, setResponseData)
{
	rocklike::NetworkMessage netMsg;
	netMsg.setResponseData(cStrRespTD, cStrRespTDLen);

	ASSERT_STREQ(cStrRespTD, netMsg.getResponseData());
	ASSERT_EQ(cStrRespTDLen, netMsg.getResponseDataSize());
}

TEST_F(NetworkMessageTest, moveAssignment)
{
	rocklike::NetworkMessage netMsg = std::move(msgSourceTD);

	ASSERT_EQ(2, newConnectionPtr.use_count());

	ASSERT_STREQ(cStrReqTD, netMsg.getRequestData());
	ASSERT_EQ(cStrReqTDLen, netMsg.getRequestDataSize());

	ASSERT_STREQ(cStrRespTD, netMsg.getResponseData());
	ASSERT_EQ(cStrRespTDLen, netMsg.getResponseDataSize());

	ASSERT_EQ(newConnectionPtr, netMsg.connStubPtr_);

	ASSERT_EQ(nullptr, msgSourceTD.getRequestData());
	ASSERT_EQ(0, msgSourceTD.getRequestDataSize());

	ASSERT_EQ(nullptr, msgSourceTD.getResponseData());
	ASSERT_EQ(0, msgSourceTD.getResponseDataSize());

	ASSERT_EQ(nullptr, msgSourceTD.connStubPtr_);

	ASSERT_EQ(0, msgSourceTD.connUseCount());
}

TEST_F(NetworkMessageTest, copyAssignment)
{
	rocklike::NetworkMessage netMsg = msgSourceTD;

	ASSERT_EQ(3, newConnectionPtr.use_count());
	ASSERT_EQ(3, netMsg.connUseCount());

	ASSERT_STREQ(msgSourceTD.getRequestData(), netMsg.getRequestData());
	ASSERT_EQ(msgSourceTD.getRequestDataSize(), netMsg.getRequestDataSize());

	ASSERT_STREQ(msgSourceTD.getResponseData(), netMsg.getResponseData());
	ASSERT_EQ(msgSourceTD.getResponseDataSize(), netMsg.getResponseDataSize());

	ASSERT_EQ(msgSourceTD.connStubPtr_, netMsg.connStubPtr_);
}

TEST_F(NetworkMessageTest, moveConstruct)
{
	rocklike::NetworkMessage netMsg(std::move(msgSourceTD));

	ASSERT_EQ(2, newConnectionPtr.use_count());

	ASSERT_STREQ(cStrReqTD, netMsg.getRequestData());
	ASSERT_EQ(cStrReqTDLen, netMsg.getRequestDataSize());

	ASSERT_STREQ(cStrRespTD, netMsg.getResponseData());
	ASSERT_EQ(cStrRespTDLen, netMsg.getResponseDataSize());

	ASSERT_EQ(newConnectionPtr, netMsg.connStubPtr_);

	ASSERT_EQ(nullptr, msgSourceTD.getRequestData());
	ASSERT_EQ(0, msgSourceTD.getRequestDataSize());

	ASSERT_EQ(nullptr, msgSourceTD.getResponseData());
	ASSERT_EQ(0, msgSourceTD.getResponseDataSize());

	ASSERT_EQ(nullptr, msgSourceTD.connStubPtr_);

	ASSERT_EQ(0, msgSourceTD.connUseCount());
}

TEST_F(NetworkMessageTest, copyConstruct)
{
	rocklike::NetworkMessage netMsg(msgSourceTD);

	ASSERT_EQ(3, newConnectionPtr.use_count());
	ASSERT_EQ(3, netMsg.connUseCount());

	ASSERT_STREQ(msgSourceTD.getRequestData(), netMsg.getRequestData());
	ASSERT_EQ(msgSourceTD.getRequestDataSize(), netMsg.getRequestDataSize());

	ASSERT_STREQ(msgSourceTD.getResponseData(), netMsg.getResponseData());
	ASSERT_EQ(msgSourceTD.getResponseDataSize(), netMsg.getResponseDataSize());

	ASSERT_EQ(msgSourceTD.connStubPtr_, netMsg.connStubPtr_);
}

TEST_F(NetworkMessageTest, setRequestDataMoreThanMaxLen)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_THROW(netMsg.setRequestData(cStrReqTD, 5000), std::length_error);
}

TEST_F(NetworkMessageTest, setsetRequestDataNull)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_THROW(netMsg.setRequestData(nullptr, 10), std::invalid_argument);
}

TEST_F(NetworkMessageTest, setsetRequestDataZeroLen)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_THROW(netMsg.setRequestData(cStrReqTD, 0), std::length_error);
}

TEST_F(NetworkMessageTest, setsetResponseDataMaxLen)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_THROW(netMsg.setResponseData(cStrRespTD, 5000), std::length_error);
}

TEST_F(NetworkMessageTest, setsetResponseDataNull)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_THROW(netMsg.setResponseData(nullptr, 10), std::invalid_argument);
}

TEST_F(NetworkMessageTest, setsetResponseDataZeroLen)
{
	rocklike::NetworkMessage netMsg;

	ASSERT_THROW(netMsg.setResponseData(cStrReqTD, 0), std::length_error);
}

} //namespace
