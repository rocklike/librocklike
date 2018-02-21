#include "rl_tcpserver.hpp"
#include <iostream>

namespace rocklike
{
/**
 * Constructor
 */
TCPServer::TCPServer(
	boost::asio::io_context &io_context,
	std::shared_ptr<MessageExtractorBase> msgExtractorPtr,
	std::shared_ptr<HandlerThreadPool> handlerThreadPoolPtr) : acceptor_(io_context), msgExtractorPtr_(msgExtractorPtr),
																	   handlerThreadPoolPtr_(handlerThreadPoolPtr) {}

/**
 * Open the acceptor
 */
void TCPServer::open(std::string bindAddr, unsigned short port_num)
{

	std::cout << "Opening server on port " << port_num << std::endl;

	boost::system::error_code ec;
	boost::asio::ip::tcp::endpoint tcpEndpoint;
	tcpEndpoint.port(port_num);

	if (bindAddr == "0.0.0.0	" || bindAddr == "0.0.0.0/0")
	{
		// bind to ANY ADDR
		tcpEndpoint.address(boost::asio::ip::address_v4::any());
	}
	else
	{
		// bind to specific ADDR
		boost::asio::ip::address_v4 ipv4Addr = boost::asio::ip::make_address_v4(bindAddr, ec);
		if (ec)
		{
			throw 1; // TODO
		}
		tcpEndpoint.address(boost::asio::ip::address(ipv4Addr));
	}

	// open, bind, listen to the specified endpoint
	this->acceptor_.open(tcpEndpoint.protocol(), ec);
	this->acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	this->acceptor_.bind(tcpEndpoint, ec);
	this->acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);

	//start accepting
	std::cout << "Listening on " << tcpEndpoint << std::endl;
	this->accept();
}

void TCPServer::accept()
{

	std::cout << "accept() " << std::endl;
	std::shared_ptr<RL_TCPConnection> newConnectionPtr = RL_TCPConnection::create(
		this->acceptor_.get_executor().context());
	newConnectionPtr->setMessageExtractor(this->msgExtractorPtr_);
	newConnectionPtr->setHandlerThreadPool(this->handlerThreadPoolPtr_);
	std::cout << "conn_use_count = " << newConnectionPtr.use_count() << std::endl;

	this->acceptor_.async_accept(newConnectionPtr->socket(),
								 boost::bind(&TCPServer::handleAccept, this, newConnectionPtr,
											 boost::asio::placeholders::error));
	std::cout << "conn_use_count = " << newConnectionPtr.use_count() << std::endl;
	std::cout << "exiting accept() " << std::endl;
}

void TCPServer::handleAccept(std::shared_ptr<RL_TCPConnection> newConnectionPtr, const boost::system::error_code &error)
{
	std::cout << "handleAccept() " << std::endl;
	std::cout << "conn_use_count = " << newConnectionPtr.use_count() << std::endl;
	if (!error)
	{
		newConnectionPtr->start();
		this->accept();
	}
	else
	{
		std::cout << error << std::endl;
	}
}

void TCPServer::wait()
{
}

void TCPServer::setIoContext(boost::asio::io_context io_context)
{
}

} //namespace rocklike