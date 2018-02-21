#ifndef FRAMEWORK_RL_TCPSERVER_H_
#define FRAMEWORK_RL_TCPSERVER_H_

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "rl_handler_thread_pool.hpp"
#include "rl_tcpconnection.hpp"

namespace rocklike
{

class TCPServer
{
  public:
	TCPServer(
		boost::asio::io_context &io_context,
		std::shared_ptr<MessageExtractorBase> msgExtractorPtr,
		std::shared_ptr<HandlerThreadPool> handlerThreadPoolPtr);
	void setIoContext(boost::asio::io_context io_context);
	void open(std::string bindAddr, unsigned short port_num);
	void accept();
	void handleAccept(std::shared_ptr<RL_TCPConnection> newConnectionPtr, const boost::system::error_code &error);
	void wait();

  private:
	//	std::string bindAddr;
	//	std::string port;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::shared_ptr<HandlerThreadPool> handlerThreadPoolPtr_;
	std::shared_ptr<MessageExtractorBase> msgExtractorPtr_;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_TCPSERVER_H_ */
