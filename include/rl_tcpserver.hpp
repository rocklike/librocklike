#ifndef FRAMEWORK_RL_TCPSERVER_H_
#define FRAMEWORK_RL_TCPSERVER_H_

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "rl_handler_thread_pool.hpp"
#include "rl_tcpconnection.hpp"

using namespace rocklike;

class RL_TCPServer {
public:
	RL_TCPServer(
			boost::asio::io_context &io_context,
			std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr,
			std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr
	);
	void setIoContext(boost::asio::io_context io_context);
	void open(std::string bindAddr, unsigned short port_num);
	void accept();
	void handleAccept(std::shared_ptr<RL_TCPConnection> newConnection, const boost::system::error_code& error);
	void wait();

private:
//	std::string bindAddr;
//	std::string port;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr_;
	std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr_;

};


#endif /* FRAMEWORK_RL_TCPSERVER_H_ */
