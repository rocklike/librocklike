#ifndef FRAMEWORK_RL_TCPCONNECTION_H_
#define FRAMEWORK_RL_TCPCONNECTION_H_

#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include <memory>

#include "rl_connection_stub.hpp"
#include "rl_handler_thread_pool.hpp"
#include "rl_networkmessage_extractor_base.hpp"

namespace rocklike
{

class RL_TCPConnection : public ConnectionStub, public std::enable_shared_from_this<RL_TCPConnection>
{
  public:

	static std::shared_ptr<RL_TCPConnection> create(boost::asio::io_context &io_context);
	// static std::shared_ptr<RL_TCPConnection> create(boost::asio::io_context &io_context,
	// 												std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr,
	// 												std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr);
	
	void setMessageExtractor(std::shared_ptr<rocklike::MessageExtractorBase>  msgExtractorPtr);
	void setHandlerThreadPool(std::shared_ptr<rocklike::HandlerThreadPool>  handlerThreadPoolPtr);
	
	boost::asio::ip::tcp::socket &socket();
	void start();
	int send_data(const char *data, const std::size_t dataLen);
	void handle_write(const boost::system::error_code &error);

	~RL_TCPConnection();

	static const std::size_t BUFF_MAX_LEN = 1024;

  private:
  	RL_TCPConnection(boost::asio::io_context &io_context);
	  
	// RL_TCPConnection(
	// 	boost::asio::io_context &io_context,
	// 	std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr,
	// 	std::shared_ptr<rocklike::HandlerThreadPool> serviceExecutorPtr

	// );

	void read_();

	void read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred);

	char readData_[BUFF_MAX_LEN + 1];
	std::size_t readDataremaining_;
	boost::asio::ip::tcp::socket socket_;
	std::shared_ptr<rocklike::MessageExtractorBase> msgExtractorPtr_;
	std::shared_ptr<rocklike::HandlerThreadPool> handlerThreadPoolPtr_;
	std::mutex sendMutex;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_TCPCONNECTION_H_ */
