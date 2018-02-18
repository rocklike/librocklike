#include "rl_tcpserver.hpp"
#include <iostream>

/**
 * Constructor
 */
RL_TCPServer::RL_TCPServer(
		boost::asio::io_context &io_context,
		std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr,
		std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr
) : acceptor_ (io_context), msgExtractorPtr_(msgExtractorPtr),
		serviceExecutorPtr_(serviceExecutorPtr) { }

/**
 * Open the acceptor
 */
void RL_TCPServer::open(std::string bindAddr, unsigned short port_num) {

	std::cout << "Opening server on port " << port_num << std::endl;

	boost::system::error_code ec;
	boost::asio::ip::tcp::endpoint tcpEndpoint;
	tcpEndpoint.port(port_num);

	if (bindAddr == "0.0.0.0	" || bindAddr == "0.0.0.0/0") {
		// bind to ANY ADDR
		tcpEndpoint.address(boost::asio::ip::address_v4::any());
	} else {
		// bind to specific ADDR
		boost::asio::ip::address_v4 ipv4Addr = boost::asio::ip::make_address_v4(bindAddr,ec);
		if (ec) {
			throw 1; // TODO
		}
		tcpEndpoint.address(boost::asio::ip::address(ipv4Addr));
	}

	// open, bind, listen to the specified endpoint
	this->acceptor_.open(tcpEndpoint.protocol() ,ec);
//	this->acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	this->acceptor_.bind(tcpEndpoint, ec);
	this->acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);

	//start accepting
	std::cout << "Listening on " << tcpEndpoint << std::endl;
	this->accept();

}

void RL_TCPServer::accept() {

	std::cout << "accept() " << std::endl;
	std::shared_ptr<RL_TCPConnection> newConnection = RL_TCPConnection::create(
			this->acceptor_.get_executor().context(),
			this->msgExtractorPtr_,
			this->serviceExecutorPtr_
	);

	this->acceptor_.async_accept(newConnection->socket(),
			boost::bind(&RL_TCPServer::handleAccept, this, newConnection,
					boost::asio::placeholders::error));
	std::cout << "exiting accept() " << std::endl;
}

void RL_TCPServer::handleAccept(std::shared_ptr<RL_TCPConnection> newConnection, const boost::system::error_code& error)
{
	std::cout << "handleAccept() " << std::endl;
	if (!error) {
		newConnection->start();
		this->accept();
	} else {
		std::cout << error << std::endl;
	}


}

void RL_TCPServer::wait() {

}

void setIoContext(boost::asio::io_context io_context) {

}
