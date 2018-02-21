#include "rl_tcpconnection.hpp"

#include <iostream>

namespace rocklike
{

// RL_TCPConnection::RL_TCPConnection(
// 	boost::asio::io_context &io_context,
// 	std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr,
// 	std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr)
// 	: RL_TCPConnection(io_context), msgExtractorPtr_(msgExtractorPtr), serviceExecutorPtr_(serviceExecutorPtr)
// {
// }

RL_TCPConnection::RL_TCPConnection(boost::asio::io_context &io_context)
	: readDataremaining_(0), socket_(io_context)
{
	memset(this->readData_, '\0', BUFF_MAX_LEN + 1);
}

RL_TCPConnection::~RL_TCPConnection()
{
	boost::system::error_code ec;
	std::cout << " Destroying TCPConnection" << std::endl;
	this->socket_.close(ec);
	std::cout << " socket close result code: " << ec << std::endl;
}

// std::shared_ptr<RL_TCPConnection> RL_TCPConnection::create(boost::asio::io_context &io_context,
// 														   std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr,
// 														   std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr)
// {
// 	RL_TCPConnection *newConn = new RL_TCPConnection(io_context, msgExtractorPtr, serviceExecutorPtr);
// 	return std::shared_ptr<RL_TCPConnection>(newConn);
// }


void RL_TCPConnection::setMessageExtractor(std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr)
{
	this->msgExtractorPtr_ = std::move(msgExtractorPtr);
}

void RL_TCPConnection::setHandlerThreadPool(std::shared_ptr<rocklike::HandlerThreadPool> handlerThreadPoolPtr)
{
	this->handlerThreadPoolPtr_ = std::move(handlerThreadPoolPtr);
}

std::shared_ptr<RL_TCPConnection> RL_TCPConnection::create(boost::asio::io_context &io_context)
{
	RL_TCPConnection *newConn = new RL_TCPConnection(io_context);
	return std::shared_ptr<RL_TCPConnection>(newConn);
}

boost::asio::ip::tcp::socket &RL_TCPConnection::socket()
{
	return this->socket_;
}

void RL_TCPConnection::start()
{
	this->read_();
}

void RL_TCPConnection::read_()
{
	std::shared_ptr<RL_TCPConnection> self(this->shared_from_this());
	std::cout << "read_() conn_use_count = " << self.use_count() << std::endl;
	this->socket_.async_read_some(
		boost::asio::buffer(this->readData_ + this->readDataremaining_, BUFF_MAX_LEN - this->readDataremaining_),
		std::bind(&RL_TCPConnection::read_handler, self, std::placeholders::_1, std::placeholders::_2));
}

void RL_TCPConnection::read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
	if (!ec)
	{
		std::cout << "read " << bytes_transferred << " bytes" << std::endl;
		std::shared_ptr<RL_TCPConnection> self(this->shared_from_this());
		// extract message(s)
		int res = this->msgExtractorPtr_->extract(this->readData_, bytes_transferred, this->readDataremaining_);

		switch (res)
		{
		case rocklike::ExtractResult::SUCCESS_CONTINUE: // read more messages
			while (!this->msgExtractorPtr_->messagesQueue().empty())
			{
				// TODO check ref ptr count of conn
				rocklike::NetworkMessage &m = this->msgExtractorPtr_->messagesQueue().front();
				m.setSourceConnection(self);
				this->handlerThreadPoolPtr_->post(m);
				this->msgExtractorPtr_->messagesQueue().pop();
				// TODO test if pop destructs the element
			}
			this->read_();
			break;
		case rocklike::ExtractResult::SUCCESSS_STOP: // client requests disconnect, no need to alarm
			break;
		case rocklike::ExtractResult::DECODE_ERROR: // message  decoding error, disconnect and log alarm
			break;
		default:
			std::cout << ""; // system error, disconnect and log alarm
		}
	}
	else
	{
		std::cout << "read_handler: " << ec << std::endl;
	}
}

int RL_TCPConnection::send_data(const char *data, const std::size_t dataLen)
{
	//int RL_TCPConnection::send_data(std::string & responseData) {

	std::shared_ptr<RL_TCPConnection> self(this->shared_from_this());

	//	const char * data = responseData.c_str();
	//	size_t dataLen = responseData.length();
	std::cout << "Sending data" << data << std::endl;
	this->socket_.async_write_some(
		boost::asio::buffer(data, dataLen),
		std::bind(&RL_TCPConnection::handle_write, self,
				  std::placeholders::_1));
	return 0;
	// TODO
}

void RL_TCPConnection::handle_write(const boost::system::error_code &error)
{
	std::lock_guard<std::mutex> guard(this->sendMutex);
	if (!error)
	{
		std::cout << "Data sen. reading again.t\n";
		// this->read_();
	}
	else
	{
	}
}

} //end namespace
