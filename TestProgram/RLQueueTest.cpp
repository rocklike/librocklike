#include "gtest/gtest.h"
#include "rl_network_message.hpp"
#include <cstring>
#include <boost/asio.hpp>
#include "rl_tcpconnection.hpp"

namespace
{

class RLQueueTest : public ::testing::Test
{
  public:  
    RLQueueTest(int size = 5) : rlQueue(size)
    {

    }

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

    rocklike::Queue<rocklike::NetworkMessage,rocklike::RlQueue> rlQueue;
    
    char cStrReqTD[50] = "Request Data";
	std::size_t cStrReqTDLen;

	char cStrRespTD[50] = "Response Data";
	std::size_t cStrRespTDLen;

	rocklike::NetworkMessage msgSourceTD;

	std::shared_ptr<rocklike::RL_TCPConnection> newConnectionPtr;

	boost::asio::io_context io_context;

};

TEST_F(RLQueueTest, pushEmptyMessage) 
{
    int currSize = rlQueue.size();
    rocklike::NetworkMessage netMsg;
    ASSERT_THROW( rlQueue.push(std::move(netMsg)), std::invalid_argument);
    
}

TEST_F(RLQueueTest, pushMessage) 
{
    int currSize = rlQueue.size();

    rlQueue.push( std::move(msgSourceTD) );

    ASSERT_EQ(0, msgSourceTD.connUseCount());
    ASSERT_EQ(2, newConnectionPtr.use_count());

    ASSERT_EQ(currSize + 1, rlQueue.size());
    
}

TEST_F(RLQueueTest, popMessage) 
{

    int currSize = rlQueue.size();

    rlQueue.push( std::move(this->msgSourceTD) );

    ASSERT_EQ(0, msgSourceTD.connUseCount());
    ASSERT_EQ(2, newConnectionPtr.use_count());

    ASSERT_EQ(currSize + 1, rlQueue.size());

    rocklike::NetworkMessage netMsg;
    bool res =  rlQueue.pop(netMsg);

    ASSERT_EQ(newConnectionPtr, netMsg.connStubPtr_);

    ASSERT_EQ(2, netMsg.connUseCount());
    ASSERT_EQ(2, newConnectionPtr.use_count());

    ASSERT_EQ(currSize, rlQueue.size());
}

TEST_F(RLQueueTest, popMessageEmptyQueue) 
{
    ASSERT_EQ(0, rlQueue.size());
    rocklike::NetworkMessage netMsg;
    bool res =  rlQueue.pop(netMsg);
    
    ASSERT_EQ(nullptr, netMsg.getRequestData());
    ASSERT_EQ(0, netMsg.getRequestDataSize());

    ASSERT_EQ(false, res);

}

// TODO test threads, wait notify

} //namespace