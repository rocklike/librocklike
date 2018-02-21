#ifndef FRAMEWORK_RL_SERVICE_GATEWAY_DELEGATE_HPP_
#define FRAMEWORK_RL_SERVICE_GATEWAY_DELEGATE_HPP_

#include "rl_network_message.hpp"

namespace rocklike
{

class ServiceGatewayDelegate
{
  public:
	virtual ~ServiceGatewayDelegate();
	virtual void onNetworkMessageReceive(NetworkMessage &netmsg) = 0;
};

} //namespace rocklike

#endif /* FRAMEWORK_RL_SERVICE_GATEWAY_DELEGATE_HPP_ */
