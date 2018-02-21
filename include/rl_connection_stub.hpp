#ifndef FRAMEWORK_RL_CONNECTION_STUB_HPP_
#define FRAMEWORK_RL_CONNECTION_STUB_HPP_

#include <memory>

namespace rocklike
{

class ConnectionStub
{

  public:
	virtual ~ConnectionStub();
	virtual int send_data(const char *data, const std::size_t dataLen) = 0;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_CONNECTION_STUB_HPP_ */
